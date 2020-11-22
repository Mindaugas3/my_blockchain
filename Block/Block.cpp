//
// Created by Mindaugas on 2020-11-06.
//

#include <iterator>
#include <cmath>
#include <iostream>
#include "Block.h"
#include "../Generators/hashes/Sha256.h"
#include "../Generators/TransactionGenerator.h"
#define EPSILON 0.01

Block::Block( vector<Transaction> copiedTransactions, string _prev, string _time, float _v, int diffT) {
    copy(copiedTransactions.begin(), copiedTransactions.end(), back_inserter(transactionsInBlock));
    copy(_prev.begin(), _prev.end(), back_inserter(prevBlockHash));
    copy(_time.begin(), _time.end(), back_inserter(timeStamp));
    blockVersion = _v;
    diffTarget = diffT;
    nonce = 0;
    string hashSum = "";
#pragma omp parallel
    do {
        nonce++;
        hashSum = getHashSum();
    } while (!startsWithZeroes(hashSum, diffT));
}

string Block::getHashSum() {
    string everything;
    everything += TransactionGenerator::getMerkleRoot(transactionsInBlock);
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
    return *this;
}

const vector<Transaction> &Block::getTransactionsInBlock() const {
    return transactionsInBlock;
}

const string &Block::getPrevBlockHash() const {
    return prevBlockHash;
}

const string &Block::getTimeStamp() const {
    return timeStamp;
}

float Block::getBlockVersion() const {
    return blockVersion;
}

const string &Block::getMerkleHash() const {
    return merkleHash;
}

int Block::getNonce() const {
    return nonce;
}

int Block::getDiffTarget() const {
    return diffTarget;
}

Block::Block(vector<Transaction> copiedTransactions, string _prev, string _time, float _v, int diffT, int copyNonce) {
    copy(copiedTransactions.begin(), copiedTransactions.end(), back_inserter(transactionsInBlock));
    copy(_prev.begin(), _prev.end(), back_inserter(prevBlockHash));
    copy(_time.begin(), _time.end(), back_inserter(timeStamp));
    blockVersion = _v;
    diffTarget = diffT;
    nonce = copyNonce;
    cout << "Returning block!" << endl;
}

bool Block::operator==(Block& block) {
    return this->prevBlockHash == block.getPrevBlockHash() &&
    this->transactionsInBlock.size() == block.getTransactionsInBlock().size() &&
    equal(this->transactionsInBlock.begin(), this->transactionsInBlock.end(), block.getTransactionsInBlock().begin()) &&
    this->timeStamp == block.getTimeStamp() &&
    User::FloatApproximatelyEquals(this->blockVersion, block.getBlockVersion()) && //version
    this->nonce == block.getNonce() &&
    this->diffTarget == block.getDiffTarget();
}

