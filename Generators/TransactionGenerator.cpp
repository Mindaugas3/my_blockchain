//
// Created by Mindaugas on 2020-11-06.
//

#include "TransactionGenerator.h"
#include "RNG.h"

vector<Transaction> TransactionGenerator::pickFromUsers(vector<User> users, int number) {
    vector<Transaction> transactions = vector<Transaction>();

    int any = RNG::rangeRandom(0, users.size());

    for(int i = 0; i < number; i++){
            //paima du userius
            User sender = users.at(any);
            any = RNG::rangeRandom(0, users.size());
            User receiver = users.at(any);
        do{
            any = RNG::rangeRandom(0, users.size());
            sender = users.at(any);
            any = RNG::rangeRandom(0, users.size());
            receiver = users.at(any);
        } while(receiver == sender); //isitikina kad nevienodi

        float amount = (float) RNG::rangeRandom(0, sender.getBalance());
        if(sender.getBalance() - amount <= 0){
            continue;
        } else {
            sender.addBalance(-1.0f*amount);
            receiver.addBalance(amount);
        }

        Transaction t = Transaction(sender, receiver, amount);
        transactions.push_back(t);
    }
    return transactions;
}
