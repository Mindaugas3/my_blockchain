//
// Created by Mindaugas on 2020-11-09.
//

#ifndef BLOCKCHN_MINER_H
#define BLOCKCHN_MINER_H

#include "../Block/Block.h"
#include <vector>
#include <algorithm>

class Miner { //bloku kasykla
    private:

    public:
    static Block Mine (vector<Transaction>& transactionPool, Block previousBlock);
    static Block genesisBlock();
    static Block fromCandidateBlocks(vector<Transaction>& transactionPool);
    static void chooseFrom(vector<Transaction> &vector, int i, std::vector<Transaction>& write);

    static string now();
};

#endif //BLOCKCHN_MINER_H
