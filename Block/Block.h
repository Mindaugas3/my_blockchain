//
// Created by Mindaugas on 2020-11-06.
//

#include "Transaction.h"
#include <string>

#ifndef BLOCKCHN_BLOCK_H
#define BLOCKCHN_BLOCK_H

#endif //BLOCKCHN_BLOCK_H

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
