#include <iostream>
#include <vector>
#include <string>
//#define _Out_writes_(x) //kada includiname mpi.h visada reikia sito!
#include <mpi.h>
#include <iomanip>

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
//#define TEST_Serialization

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
        for(int i = 0; i < 1200; i++){ //1200 testu transakcijoms
            int any = RNG::rangeRandom(0, transactionsPool.size());
            Transaction exampleTransaction = transactionsPool[any];
            string serializedTransaction = Serializer::serializeTransaction(exampleTransaction);
            Transaction deserialized = Serializer::deserializeTransaction(serializedTransaction);
            cout << fixed ;
            cout << setprecision(3);
            if(deserialized == exampleTransaction) cout << "TRUE" << endl << endl; else {
                cout << "FALSE" << endl;
                cout << "Sender: " << (deserialized.getSender() == exampleTransaction.getSender()) << endl;
                cout << "Receiver: " << (deserialized.getReceiver() == exampleTransaction.getReceiver()) << endl; //klaida
                cout << "Receiver: " << deserialized.getReceiver().getBalance() << " : " << exampleTransaction.getReceiver().getBalance() << endl; //klaida
                if(User::FloatApproximatelyEquals(deserialized.getReceiver().getBalance(), exampleTransaction.getReceiver().getBalance())) cout << "Receiver balance IDENTICAL" << endl;
                else cout << "FLOAT COMPARISON ERROR @ getReceiver().getBalance()" << endl;
                cout << "Sender: " << deserialized.getAmount() << " : " << exampleTransaction.getAmount() << endl;
            }
        }

        vector<Transaction> randomTestTransactions = TransactionGenerator::pickFromUsers(users, 2);
        Block testBlock = Block(randomTestTransactions, "whatever", "wedontcareabouttime", 2, 3, 2524);
        string serializedBlock = Serializer::serializeBlock(testBlock);
        cout << serializedBlock << endl << endl;
        Block deserializedBlock = Serializer::deserializeBlock(serializedBlock);
        if(deserializedBlock == testBlock) cout << "Blokai : TRUE" << endl; else cout << "FALSE" << endl;
        system("PAUSE");
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

        char blockBuffer [27000];
        MPI_Barrier(MPI_COMM_WORLD);

        MPI_Recv(&blockBuffer, 27000, MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        cout << "Gautas blokas!" << endl << endl;
        string serializedGenesisBlock(blockBuffer);
        //cout << serializedGenesisBlock << endl;
        genesisBlock = Serializer::deserializeBlock(serializedGenesisBlock);
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

            } else std::terminate();
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

        Block genesisBlock = Miner::genesisBlock(transactionsPool);
        string serializedGenesis = Serializer::serializeBlock(genesisBlock);
        char blockbuffer[27000];

        strcpy(blockbuffer, serializedGenesis.c_str());
        MPI_Send(&blockbuffer, 27000, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        cout << "Siunciamas genesis blokas is proceso : #" << procid << endl;
        while(true){
            MPI_Barrier(MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}


