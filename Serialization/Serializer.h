//
// Created by Mindaugas on 2020-11-21.
//

#ifndef BLOCKCHN_SERIALIZER_H
#define BLOCKCHN_SERIALIZER_H

#include "../Block/Transaction.h"
#include "../Block/User.h"
#include <sstream>

using namespace std;
class Serializer{
    public:
        //transaction
        static Transaction TransactionFromString(string transactionStr);
        static string TransactionToString(Transaction& transaction);
        //block
};

#endif //BLOCKCHN_SERIALIZER_H
