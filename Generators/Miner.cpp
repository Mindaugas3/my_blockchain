//
// Created by Mindaugas on 2020-11-09.
//

#include <ctime>
#include "Miner.h"

#include "RNG.h"

Block Miner::Mine(vector<Transaction> &transactionPool, Block previousBlock) {
    vector<Transaction> blockTransactions;
    chooseFrom(transactionPool, 100, blockTransactions);
    string prevBlockHash = previousBlock.getHashSum();
    string time = now();
    float version = 0.1;
    int difficulty = 5;

    return Block(blockTransactions, prevBlockHash, time, version, difficulty);
}

Block Miner::genesisBlock(vector<Transaction>& transactionPool) {
    vector<Transaction> blockTransactions;
    chooseFrom(transactionPool, 100, blockTransactions);
    string prevBlock = "000000000000000000000000000000000000000000";
    string time = now();
    float version = 0.1;
    int difficulty = 5;

    return Block(blockTransactions, prevBlock, time, version, difficulty);
}

void Miner::chooseFrom(vector<Transaction>& transactionPool, int amount, vector<Transaction>& writeTo){
    int any = RNG::rangeRandom(0, transactionPool.size());


    for(int i = 0; i < amount; i++){
        Transaction transaction = transactionPool.at(any);
        writeTo.push_back(transaction);
        transactionPool.erase(transactionPool.begin() + any);
    }
}

string Miner::now(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[90];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
    std::string str(buffer);
    return str;
}