//
// Created by Mindaugas on 2020-11-09.
//

#include "Miner.h"
#include "RNG.h"

void Miner::Mine(const vector<Transaction> &transactionPool, vector<Block> &blockChain) {

}

Block Miner::genesisBlock(const vector<Transaction>& transactionPool) {
    vector<Transaction> blockTransactions = chooseFrom(transactionPool, 100);
    return Block();
}

vector<Transaction> Miner::chooseFrom(const vector<Transaction>& transactionPool, int amount){
    vector<Transaction> transactionsChosen;
    int any = RNG::rangeRandom(0, transactionPool.size());


    for(int i = 0; i < amount; i++){
        Transaction transaction = transactionPool.at(any);
        transactionsChosen.push_back(transaction);
    }
}