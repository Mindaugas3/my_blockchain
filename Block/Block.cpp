//
// Created by Mindaugas on 2020-11-06.
//

#include "Block.h"
#include "../Generators/hashes/Hash_Generator.h"
#include "../Generators/hashes/Sha256.h"

Block::Block( vector<Transaction> copiedTransactions, string _prev, string _time, float _v, int diffT) {
    copy(copiedTransactions.begin(), copiedTransactions.end(), back_inserter(transactionsInBlock));
    copy(_prev.begin(), _prev.end(), back_inserter(prevBlockHash));
    copy(_time.begin(), _time.end(), back_inserter(timeStamp));
    blockVersion = _v;
    diffTarget = diffT;
    nonce = 0;
    string hashSum = "";
    do {
        nonce++;
        hashSum = getHashSum();
    } while (!startsWithZeroes(hashSum, diffT));
}

string Block::getHashSum() {
    string everything;
    for(Transaction t : transactionsInBlock){
        everything += t.getHash();
    }
    everything += " : ";
    everything += prevBlockHash;
    everything += " : ";
    everything += timeStamp;
    everything += " : ";
    everything += blockVersion;
    everything += " : ";
    everything += to_string(nonce);
    everything += " : ";
    everything += timeStamp;
    everything += " : ";
    everything += to_string(diffTarget);
    everything += " : ";
    everything += to_string(nonce);
    string hash = sha256(everything);
    return hash;
}

bool Block::startsWithZeroes(string str, int diff){
    string start;
    for(int i = 0; i < diff; i++) start += to_string(0);
    return str.rfind(start, 0) == 0;
}

Block::Block(const Block &block) {
    copy(block.transactionsInBlock.begin(), block.transactionsInBlock.end(), back_inserter(transactionsInBlock));
    prevBlockHash = block.prevBlockHash;
    timeStamp = block.timeStamp;
    blockVersion = block.blockVersion;
    merkleHash = block.merkleHash;
    nonce = block.nonce;
    diffTarget = block.diffTarget;
}

Block &Block::operator=(const Block &block) {
    copy(block.transactionsInBlock.begin(), block.transactionsInBlock.end(), back_inserter(transactionsInBlock));
    prevBlockHash = block.prevBlockHash;
    timeStamp = block.timeStamp;
    blockVersion = block.blockVersion;
    merkleHash = block.merkleHash;
    nonce = block.nonce;
    diffTarget = block.diffTarget;
}

