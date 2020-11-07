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
};

#endif //BLOCKCHN_TRANSACTION_H
