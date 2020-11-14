//
// Created by Mindaugas on 2020-11-09.
//

#ifndef BLOCKCHN_MINER_H
#define BLOCKCHN_MINER_H

#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <ctime>
#include <stdexcept>
#include "RNG.h"
#include "VerifyTransaction.h"
#include "../Block/Block.h"

#define TIME_LIMIT_MINUTES 1
#define difficulty 3

class Miner { //bloku kasykla

    public:
#ifdef MPI_PARALLEL_
    static int _ierr, _procid, _numprocs;
    static void init(int ierr, int procid, int numprocs);
#endif

    static Block Mine (vector<Transaction>& transactionPool, Block previousBlock);
    static Block genesisBlock(vector<Transaction>& transactionPool);
    static Block fromCandidateBlocks(vector<Transaction>& transactionPool);
    static Block fromParallel(vector<Transaction>& transactionPool);
    static void chooseFrom(vector<Transaction> &vector, int i, std::vector<Transaction>& write);

    static string now();
};

#endif //BLOCKCHN_MINER_H
