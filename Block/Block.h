//
// Created by Mindaugas on 2020-11-06.
//
#pragma once
#ifndef BLOCKCHN_BLOCK_H
#define BLOCKCHN_BLOCK_H

#include "Transaction.h"
#include <string>
#include <vector>

class Block {
    private:
        vector<Transaction> transactionsInBlock;
        string prevBlockHash;
        string timeStamp;
        float blockVersion;
        string merkleHash;
        int nonce;
        int diffTarget;
    public:
        Block(vector<Transaction> copiedTransactions, string _prev, string _time, float _v, int diffT);
        string getHashSum();

    static bool startsWithZeroes(string basicString, int amount);
};
#endif //BLOCKCHN_BLOCK_H