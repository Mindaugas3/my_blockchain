//
// Created by Mindaugas on 2020-11-06.
//
#pragma once
#ifndef BLOCKCHN_BLOCK_H
#define BLOCKCHN_BLOCK_H

#include "Transaction.h"
#include <string>
#include <vector>
#include <algorithm>

class Block {
private:
        vector<Transaction> transactionsInBlock;
public:
    const vector<Transaction> &getTransactionsInBlock() const;

    const string &getPrevBlockHash() const;

    const string &getTimeStamp() const;

    float getBlockVersion() const;

    const string &getMerkleHash() const;

    int getNonce() const;

    int getDiffTarget() const;

private:
    string prevBlockHash;
        string timeStamp;
        float blockVersion;
        string merkleHash;
        int nonce;
        int diffTarget;
    public:
        Block() = default;
        Block(vector<Transaction> copiedTransactions, string _prev, string _time, float _v, int diffT);
        Block(vector<Transaction> copiedTransactions, string _prev, string _time, float _v, int diffT, int copyNonce);
        string getHashSum();
        Block(const Block& block);
        Block& operator=(const Block& block);
        bool operator==(Block& block);

    static bool startsWithZeroes(string basicString, int amount);
};
#endif //BLOCKCHN_BLOCK_H