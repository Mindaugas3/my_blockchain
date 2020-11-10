
//
// Created by Mindaugas on 2020-11-06.
//
#pragma once
#ifndef BLOCKCHN_CANDIDATEBLOCK_H
#define BLOCKCHN_CANDIDATEBLOCK_H

#include "Transaction.h"
#include "Block.h"
#include <string>
#include <vector>
#include <algorithm>

//blokas-kandidatas. Pirma reikia patikrinti transakcijas, ir tada pasirinkti bloka arba ji ismesti

class CandidateBlock : public Block {
private:
    vector<Transaction> transactionsInBlock;
    string prevBlockHash;
    string timeStamp;
    float blockVersion;
    string merkleHash;
    int nonce;
    int diffTarget;
public:
    CandidateBlock(vector<Transaction> copiedTransactions, string _prev, string _time, float _v, int diffT);
    string getHashSum();
    CandidateBlock(const CandidateBlock& block);
    CandidateBlock& operator=(const CandidateBlock& block);

    static bool startsWithZeroes(string basicString, int amount);
};

#endif //BLOCKCHN_CANDIDATEBLOCK_H
