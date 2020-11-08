//
// Created by Mindaugas on 2020-11-06.
//

#ifndef BLOCKCHN_TRANSACTION_H
#define BLOCKCHN_TRANSACTION_H

#include <string>
#include "User.h"
using namespace std;

class Transaction{
    private:
        string transactionHash;
        User sender;
        User receiver;
        float amount;
    public:
        Transaction(const User& _sender, const User& _receiver, float _amount);
        string getHash();
        User getSender();
        User getReceiver();
        float getAmount();
};

#endif //BLOCKCHN_TRANSACTION_H
