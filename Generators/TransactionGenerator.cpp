//
// Created by Mindaugas on 2020-11-06.
//

#include <algorithm>
#include "TransactionGenerator.h"
#include "RNG.h"
#include "hashes/Hash_Generator.h"

vector<Transaction> TransactionGenerator::pickFromUsers(vector<User> users, int number) {
    vector<Transaction> transactions = vector<Transaction>();

    int any = RNG::rangeRandom(0, users.size());
#pragma omp parallel for
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

string TransactionGenerator::getMerkleRoot(const vector<Transaction> &transactionPool) {
    vector<Transaction> transactions = transactionPool;
    sort(transactions.begin(), transactions.end(),
            [](const Transaction& a, const Transaction& b) -> bool //lambda funkcija rikiavimui
            {
                return a.getHash() > b.getHash();
            });
    vector<string> level;
#pragma omp parallel for
    for(const Transaction& t : transactions){
        level.push_back(t.getHash());
    }
    //gauname sakni
    while(level.size() > 1){
        vector<string> higherLevel;
        if(level.size() % 2 != 0){
            level.push_back(level.at(level.size() - 1));
        }
        for(int i = 0; i < level.size(); i+=2){
            Hash_Generator hgen = Hash_Generator(level.at(i) + level.at(i+1));
            higherLevel.push_back(hgen.getHash());
        }

        level = higherLevel;
    }

    return level.at(0);
}


