#include <iostream>
#include <vector>
#include <string>
//#define _Out_writes_(x) //kada includiname mpi.h visada reikia sito!
#include <mpi.h>

#include "Block/User.h"
#include "Generators/UserGenerator.h"
#include "Block/Transaction.h"
#include "Generators/TransactionGenerator.h"
#include "Block/Block.h"
#include "Generators/Miner.h"
#include "Serialization/Serializer.h"


using namespace std;

#define parallel_MPI_
#define TEST_Genesis
#define TEST_Serialization

int main(int argc, char** argv) {

    MPI_Init(NULL, NULL);

    int procid;
    int numprocs;

    MPI_Comm_rank(MPI_COMM_WORLD, &procid);  //rank
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs); //cores



    if (procid == 0)
    {
        cout << "Master procesas" << endl;
        vector<User> users;
        UserGenerator::generateUsers(users, 1000); //nauji useriai

        vector<Transaction> transactionsPool = TransactionGenerator::pickFromUsers(users, 10000);
        cout << "Sukurtos transakcijos!" << endl;


#ifdef TEST_Serialization
        int any = RNG::rangeRandom(0, transactionsPool.size());
        Transaction exampleTransaction = transactionsPool[any];
        string serializedTransaction = Serializer::serializeTransaction(exampleTransaction);
        cout << serializedTransaction << endl;
        Transaction deserialized = Serializer::deserializeTransaction(serializedTransaction);
        if(deserialized == exampleTransaction) cout << "TRUE" << endl << endl;

        vector<Transaction> randomTestTransactions = TransactionGenerator::pickFromUsers(users, 5);
        Block testBlock = Block(randomTestTransactions, "whatever", "wedontcareabouttime", 2, 3, 2524);
        string serializedBlock = Serializer::serializeBlock(testBlock);
        cout << serializedBlock << endl << endl;
        Block deserializedBlock = Serializer::deserializeBlock(serializedBlock);
        if(deserializedBlock == testBlock) cout << "TRUE" << endl;
#endif

        vector<Block> blockChain;
        cout << "Renkami blokai kandidatai: " << endl;

        MPI_Status status;

        char singleTransactionBuffer[256];
        for(Transaction& transaction : transactionsPool){
            char singleTransactionBuffer[256];
            string serialized = Serializer::serializeTransaction(transaction);
            strcpy(singleTransactionBuffer, serialized.c_str());
            MPI_Bcast(singleTransactionBuffer, 256, MPI_CHAR, 0, MPI_COMM_WORLD);
        }
        //send transaction pool

        cout << "Issiustas transakciju baseinas!" << endl;
        //receive block

        Block genesisBlock;
        MPI_Barrier(MPI_COMM_WORLD);

        MPI_Recv(&genesisBlock, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        cout << "Gautas blokas!" << endl;
        //
        blockChain.push_back(genesisBlock);

#ifdef TEST_Genesis
        cout << "Sukurto genesis bloko hash suma: " << blockChain.at(0).getHashSum() << endl;
        cout << endl << "Kasyklos dydis: " << transactionsPool.size() << endl;

#endif
        string command;
        cout << "-mine : Kasti bloka" << endl;
        Block lastBlockUsed = genesisBlock;
        while (cin >> command) {
            if (command == "-mine") {
                while (!transactionsPool.empty()) {
                    Block minedBlock = Miner::Mine(transactionsPool, lastBlockUsed);
                    blockChain.push_back(minedBlock);
                    cout << "Iskasto bloko hash suma: " << minedBlock.getHashSum() << endl;
                    lastBlockUsed = minedBlock;

                    cout << endl << "Kasyklos dydis: " << transactionsPool.size() << endl;
                }

            }
        }
    } else {
        vector<Transaction> transactionsPool;
        transactionsPool.reserve(10000);

        MPI_Status recStatus;
        MPI_Barrier(MPI_COMM_WORLD);
        for(int i = 0; i < 10000; i++){
            char singleTransactionBuffer[256];
            MPI_Bcast(singleTransactionBuffer, 256, MPI_CHAR, 0, MPI_COMM_WORLD);
            string fromBuffer(singleTransactionBuffer);
            Transaction deserialized = Serializer::deserializeTransaction(fromBuffer);
            //cout << i << " Received: " << fromBuffer << endl;
            transactionsPool.push_back(deserialized);
        }


        cout << "Gautas transakciju baseinas : procesas-vergas #" << procid << endl;

        Block genesisBlock = Miner::genesisBlock(transactionsPool); //SIGSEGV

        MPI_Send(&genesisBlock, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        cout << "Siunciamas genesis blokas " << endl;
        MPI_Barrier(MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
