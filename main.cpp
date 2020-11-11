#include <iostream>
#include <vector>
#include <string>
#include "Block/User.h"
#include "Generators/UserGenerator.h"
#include "Block/Transaction.h"
#include "Generators/TransactionGenerator.h"
#include "Block/Block.h"
#include "Generators/Miner.h"

using namespace std;

#define TEST_Genesis

int main() {

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
    return 0;
}
