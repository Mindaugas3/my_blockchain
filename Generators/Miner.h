//
// Created by Mindaugas on 2020-11-09.
//

#ifndef BLOCKCHN_MINER_H
#define BLOCKCHN_MINER_H

#include "../Block/Block.h"
#include <vector>
#include <algorithm>
#include <mpi.h>

class Miner { //bloku kasykla

    public:



    static Block Mine (vector<Transaction>& transactionPool, Block previousBlock);
    static Block genesisBlock(vector<Transaction>& transactionPool);
    static Block fromCandidateBlocks(vector<Transaction>& transactionPool);
    static void chooseFrom(vector<Transaction> &vector, int i, std::vector<Transaction>& write);

    static string now();
};

#endif //BLOCKCHN_MINER_H
