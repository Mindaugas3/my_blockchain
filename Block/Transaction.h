//
// Created by Mindaugas on 2020-11-06.
//
#pragma once
#ifndef BLOCKCHN_TRANSACTION_H
#define BLOCKCHN_TRANSACTION_H

#include <string>
#include "User.h"
using namespace std;

class Transaction{
    private:
        string transactionHash = "";
        User sender;
        User receiver;
        float amount;
    public:
        explicit Transaction(User sender, User _receiver, float _amount);
        Transaction(const Transaction &transaction, User receiver, User sender);
        string getHash() const;
        User getSender();
        User getReceiver();
        float getAmount();
        ~Transaction();
};

#endif //BLOCKCHN_TRANSACTION_H
