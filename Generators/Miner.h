//
// Created by Mindaugas on 2020-11-09.
//

#ifndef BLOCKCHN_MINER_H
#define BLOCKCHN_MINER_H

#include "../Block/Block.h"
#include <vector>

class Miner {
    private:

    public:
    static void Mine (vector<Transaction>& transactionPool, vector<Block>& blockChain);
    static Block genesisBlock(vector<Transaction>& transactionPool);

    static vector<Transaction> chooseFrom(const vector<Transaction> &vector, int i);

    static string now();
};

#endif //BLOCKCHN_MINER_H
