//
// Created by Mindaugas on 2020-11-21.
//

#ifndef BLOCKCHN_SERIALIZER_H
#define BLOCKCHN_SERIALIZER_H

#include "../Block/Transaction.h"
#include "../Block/User.h"
#include "../Block/Block.h"
#include <sstream>

using namespace std;
class Serializer{
    public:
        //transaction
        static Transaction deserializeTransaction(string transactionStr);
        static string serializeTransaction(Transaction& transaction);
        //block
        static Block deserializeBlock(string blockStr);
        static string serializeBlock(Block& block);
};

#endif //BLOCKCHN_SERIALIZER_H
