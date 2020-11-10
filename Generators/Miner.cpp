//
// Created by Mindaugas on 2020-11-09.
//

#include <ctime>
#include "Miner.h"
#include <iostream>
#include <chrono>
#include <stdexcept>
#include "RNG.h"
#include "VerifyTransaction.h"

#define TIME_LIMIT_MINUTES 5

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

Block Miner::fromCandidateBlocks(vector<Transaction>& transactionPool){
    //inicializuojame blokus-kandidatus
    vector<vector<Transaction>> candidateTransactionPools;

    for(int i = 5; i > 0; i--){
        vector<Transaction> singlePotentialBlock;
        chooseFrom(transactionPool, 100, singlePotentialBlock);
        candidateTransactionPools.push_back(singlePotentialBlock);
    }
    //inicializuojame kitus duomenis
    string prevBlock = "000000000000000000000000000000000000000000";
    string time = now();
    float version = 0.1;
    int difficulty = 5;
    //kasame bloka
    while(!candidateTransactionPools.empty()){
        auto start = chrono::system_clock::now();
        Block candidateBlock = Block(candidateTransactionPools.at(candidateTransactionPools.size() - 1),
                prevBlock,
                time,
                version,
                difficulty);
        auto end = chrono::system_clock::now();

        chrono::duration<double> seconds_time = end - start;
        cout << "Uztruko: " << seconds_time.count() << " laiko  " << endl;
        if(seconds_time.count() > TIME_LIMIT_MINUTES*60){ //geras? Iseiname is funkcijos ir graziname bloka kandidata
            return candidateBlock;
        } else {
            candidateTransactionPools.erase(candidateTransactionPools.end());
        }
    }
    throw std::runtime_error("Netinkamai sukonfiguruotas blockchainas - kandidatas blokas renkamas per ilgai!");
}

void Miner::chooseFrom(vector<Transaction>& transactionPool, int amount, vector<Transaction>& writeTo){
    int any = RNG::rangeRandom(0, transactionPool.size());

    for(int i = 0; i < amount; i++){
        Transaction transaction = transactionPool.at(any);
        if(VerifyTransaction::verify(transaction) && VerifyTransaction::senderHasEnoughCredits(transaction)){
            //patikrina ar informacija ir hash kodas sutampa
            //patikrina ar pakankamai kreditu turi vartotojas
            writeTo.push_back(transaction);
            transactionPool.erase(transactionPool.begin() + any);
        } else {
            cout << "Transakcija bloga!" << endl;
            transactionPool.erase(transactionPool.begin() + any);
        }
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