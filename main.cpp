#include <iostream>
#include <vector>
#include <string>
#include "Block/User.h"
#include "Generators/UserGenerator.h"
#include "Block/Transaction.h"
#include "Generators/TransactionGenerator.h"
#include "Generators/hashes/Hash_Generator.h"
#include "Block/Block.h"
#include "Generators/Miner.h"

using namespace std;

int main() {

    vector<User> users;
    UserGenerator::generateUsers(users, 1000); //nauji useriai

#ifdef TEST_usersTransactions
    for(const User& u : users){
        cout << u.getName() << " : " << u.getKey() << " : " << u.getBalance() << endl;
    }
#endif
    vector<Transaction> transactionsPool = TransactionGenerator::pickFromUsers(users, 10000);
#ifdef TEST_usersTransactions
    for(Transaction t : transactionsPool){
        cout << "Transaction:" << t.getHash() << " : " << t.getSender().getName() << " : " << t.getReceiver().getName() << " : " << t.getAmount() << endl;
    }
#endif

    vector<Block> blockChain;
    blockChain.push_back(Miner::genesisBlock(blockChain));


    system("PAUSE");
    return 0;
}
