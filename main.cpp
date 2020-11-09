#include <iostream>
#include <vector>
#include <string>
#include "Block/User.h"
#include "Generators/UserGenerator.h"
#include "Block/Transaction.h"
#include "Generators/TransactionGenerator.h"
#include "Generators/hashes/Hash_Generator.h"

using namespace std;

int main() {
    cout << "anything";
    User _user = User("a");
    cout << "test user: " << _user.getKey() << " : " << _user.getBalance();
    vector<User> users;
    UserGenerator::generateUsers(users, 1000); //nauji useriai


    for(User u : users){
        cout << u.getName() << " : " << u.getKey() << " : " << u.getBalance() << endl;
    }
    vector<Transaction> transactionsPool = TransactionGenerator::pickFromUsers(users, 10000);
    for(Transaction t : transactionsPool){
        cout << t.getHash() << " : " << t.getSender().getName() << " : " << t.getReceiver().getName() << " : " << t.getAmount() << endl;
    }
    system("PAUSE");
    return 0;
}
