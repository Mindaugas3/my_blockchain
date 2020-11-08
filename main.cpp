#include <iostream>
#include <vector>
#include <string>
#include "Block/User.h"
#include "Generators/UserGenerator.h"
#include "Block/Transaction.h"
#include "Generators/TransactionGenerator.h"
using namespace std;

int main() {
    cout << "anything";
    vector<User> users = UserGenerator::generateUsers(1000); //nauji useriai
    User user = User("some random user");

    cout << user.getName() << " : "<<user.getKey() << endl;

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
