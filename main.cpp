#include <iostream>
#include <vector>
#include <string>

#define _Out_writes_(x) //kada includiname mpi.h visada reikia sito!

#include "mpi.h"

#include "Block/User.h"
#include "Generators/UserGenerator.h"
#include "Block/Transaction.h"
#include "Generators/TransactionGenerator.h"
#include "Block/Block.h"
#include "Generators/Miner.h"



using namespace std;

#define parallel_MPI_
#define TEST_Genesis

int main(int argc, char** argv) {


    MPI_Init(NULL, NULL);

    int procid;
    int numprocs;

    MPI_Comm_rank(MPI_COMM_WORLD, &procid);  //rank
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs); //cores

    vector<User> users;
    UserGenerator::generateUsers(users, 1000); //nauji useriai

cout << "Sukurti vartotojai!" << endl;

    vector<Transaction> transactionsPool = TransactionGenerator::pickFromUsers(users, 10000);
cout << "Sukurtos transakcijos!" << endl;


    vector<Block> blockChain;
    cout << "Renkami blokai kandidatai: " << endl;
    Block genesisBlock = Miner::fromCandidateBlocks(transactionsPool);
    blockChain.push_back(genesisBlock);

#ifdef TEST_Genesis
    cout << "Sukurto genesis bloko hash suma: " << blockChain.at(0).getHashSum() << endl;
    cout << endl << "Kasyklos dydis: " << transactionsPool.size() << endl;

#endif
    string command;
    cout << "-mine : Kasti bloka" << endl;
    Block lastBlockUsed = genesisBlock;
    while (cin >> command){
        if(command == "-mine"){
            while(!transactionsPool.empty()){
                Block minedBlock = Miner::Mine(transactionsPool, lastBlockUsed);
                blockChain.push_back(minedBlock);
                cout << "Iskasto bloko hash suma: " << minedBlock.getHashSum() << endl;
                lastBlockUsed = minedBlock;

                cout << endl << "Kasyklos dydis: " << transactionsPool.size() << endl;
            }

        }
    }
    MPI_Finalize();
    return 0;
}
