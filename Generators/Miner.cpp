//
// Created by Mindaugas on 2020-11-09.
//


#include "Miner.h"



Block Miner::Mine(vector<Transaction> &transactionPool, Block previousBlock) {
    vector<Transaction> blockTransactions;
    chooseFrom(transactionPool, 100, blockTransactions);
    string prevBlockHash = previousBlock.getHashSum();
    string time = now();
    float version = 0.1;

    return Block(blockTransactions, prevBlockHash, time, version, difficulty);
}

Block Miner::genesisBlock(vector<Transaction>& transactionPool) {
    vector<Transaction> blockTransactions;
    chooseFrom(transactionPool, 100, blockTransactions);
    string prevBlock = "000000000000000000000000000000000000000000";
    string time = now();
    float version = 0.1;

    return Block(blockTransactions, prevBlock, time, version, difficulty);
}

Block Miner::fromCandidateBlocks(vector<Transaction>& transactionPool){

    //inicializuojame blokus-kandidatus
    vector<vector<Transaction>> candidateTransactionPools;
    vector<vector<Transaction>> discardedTransactions; //jeigu blokas atmetamas

    for(int i = 5; i > 0; i--){
        vector<Transaction> singlePotentialBlock;
        chooseFrom(transactionPool, 100, singlePotentialBlock);
        candidateTransactionPools.push_back(singlePotentialBlock);
    }
    //inicializuojame kitus duomenis
    string prevBlock = "000000000000000000000000000000000000000000";
    string time = now();
    float version = 0.1;
    //kasame bloka
    while(!candidateTransactionPools.empty()){
        auto start = chrono::system_clock::now();
        size_t candidatePS = candidateTransactionPools.size();
        Block candidateBlock = Block(candidateTransactionPools.at(candidateTransactionPools.size() - 1),
                prevBlock,
                time,
                version,
                difficulty);
        auto end = chrono::system_clock::now();

        chrono::duration<double> seconds_time = end - start;
        cout << "Uztruko: " << seconds_time.count() << " laiko  " << endl;
        if(seconds_time.count() < TIME_LIMIT_MINUTES*60){ //geras? Iseiname is funkcijos ir graziname bloka kandidata
            return candidateBlock;
        } else {
            candidateTransactionPools.erase(candidateTransactionPools.end());
            continue;
        }
    }
    throw std::runtime_error("Netinkamai sukonfiguruotas blockchainas - kandidatas blokas renkamas per ilgai!");
}

void Miner::chooseFrom(vector<Transaction>& transactionPool, int amount, vector<Transaction>& writeTo){
    int any = RNG::rangeRandom(0, transactionPool.size());

    while(writeTo.size() < 100){ //paima butent 100 TINKAMU transakciju. Kitas meta lauk is kasyklos
        Transaction transaction = transactionPool.at(any);
        if(VerifyTransaction::verify(transaction) && VerifyTransaction::senderHasEnoughCredits(transaction)){
            //patikrina ar informacija ir hash kodas sutampa
            //patikrina ar pakankamai kreditu turi vartotojas
            writeTo.push_back(transaction);
            transactionPool.erase(transactionPool.begin() + any);
        } else {
            string message;
            if(!VerifyTransaction::verify(transaction)) message = " Hasai nesutampa ";
            if(!VerifyTransaction::senderHasEnoughCredits(transaction)) message = " Kreditu neuztenka! ";
            cout << "Transakcija bloga! " << message << endl;
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

Block Miner::fromParallel(vector<Transaction> &transactionPool) {
    



    return Block(transactionPool, "", now(), 0, 0);
}

#ifdef MPI_PARALLEL_
void Miner::init(int ierr, int procid, int numprocs) {
    _ierr = ierr;
    _procid = procid;
    _numprocs = numprocs;
}
#endif