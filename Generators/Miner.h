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
    static void Mine (const vector<Transaction>& transactionPool, vector<Block>& blockChain);
    static Block genesisBlock(const vector<Transaction>& transactionPool);
};

#endif //BLOCKCHN_MINER_H
