#include <iostream>
#include <vector>
#include <string>
#include "Block/User.h"
#include "Generators/UserGenerator.h"
#include "Block/Transaction.h"
#include "Generators/TransactionGenerator.h"

int main() {
    vector<User> users = UserGenerator::generateUsers(1000); //nauji useriai
    for(User u : users){
        cout << u.getName() << " : " << u.getKey() << " : " << u.getBalance() << endl;
    }
    vector<Transaction> transactions = TransactionGenerator::pickFromUsers(users, 10000);
    for(Transaction t : transactions){
        cout << t.getHash() << " : " << t.getSender().getName() << " : " << t.getReceiver().getName() << " : " << t.getAmount() << endl;
    }

    return 0;
}
