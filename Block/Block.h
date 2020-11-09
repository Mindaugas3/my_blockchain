//
// Created by Mindaugas on 2020-11-06.
//
#pragma once
#ifndef BLOCKCHN_BLOCK_H
#define BLOCKCHN_BLOCK_H

#include "Transaction.h"
#include <string>

class Block {
    private:
        static const int amount = 100;
        Transaction transactions[amount];
        string prevBlockHash;
        string timeStamp;
        float blockVersion;
        string merkleHash;
        int nonce;
        int diffTarget;
};
#endif //BLOCKCHN_BLOCK_H