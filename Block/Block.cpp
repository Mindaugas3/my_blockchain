//
// Created by Mindaugas on 2020-11-06.
//

#include "Block.h"
#include "../Generators/hashes/Hash_Generator.h"

Block::Block(const vector<Transaction>& copiedTransactions, string _prev, string _time, float _v, int diffT) {
    copy(copiedTransactions.begin(), copiedTransactions.end(), back_inserter(transactionsInBlock));
    prevBlockHash = _prev;
    timeStamp = _time;
    blockVersion = _v;
    int nonce_ = 0;
    do {
        nonce++;
    } while (!startsWithZeroes(this->getHashSum(), diffT));
    nonce = nonce_;
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
    Hash_Generator hgen = Hash_Generator(everything);
    return hgen.getHash();
}

bool Block::startsWithZeroes(string str, int diff){
    string start;
    for(int i = 0; i < diff; i++) start += to_string(0);
    if(str.rfind(start, 0) == 0) return true;
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

