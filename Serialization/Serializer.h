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
        static Transaction deserializeTransaction(const string& transactionStr);
        static string serializeTransaction(Transaction& transaction);
        //block
        static Block deserializeBlock(const string &blockStr, const vector<Transaction> &trVec);
        static string serializeBlock(Block& block);


};

#endif //BLOCKCHN_SERIALIZER_H
