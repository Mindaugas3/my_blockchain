//
// Created by Mindaugas on 2020-11-21.
//

#include <iostream>
#include <iomanip>
#include "Serializer.h"

Transaction Serializer::deserializeTransaction(string transactionStr) {
    stringstream input(transactionStr);
    //transaction data
    string hash;
    float amount;
    //user data
    string senderName;
    string senderKey;
    float senderBalance;
    string receiverName;
    string receiverKey;
    float receiverBalance;

    input >> hash >> amount
    >> senderName >> senderKey >> senderBalance
    >> receiverName >> receiverKey >> receiverBalance;
    //reconstruct
    User sender = User(senderName, senderKey, senderBalance);
    User receiver = User(receiverName, receiverKey, receiverBalance);
    return Transaction(sender, receiver, amount);
}

string Serializer::serializeTransaction(Transaction& transaction) {
    //decompose
    User sender = transaction.getSender(); //ne elementarus
    User receiver = transaction.getReceiver(); //ne elementarus
    string hash = transaction.getHash();
    float amount = transaction.getAmount();
    //decompose users
    string sender_key = sender.getKey();
    string receiver_key = receiver.getKey();
    string senderName = sender.getName();
    string receiverName = receiver.getName();
    float senderBalance = sender.getBalance();
    float receiverBalance = receiver.getBalance();
    //add strings together
    stringstream output;
    output << fixed;
    output << setprecision(4);
    output << hash << " " << amount << " "
    << senderName << " " << sender_key << " " << senderBalance << " "
    << receiverName << " " << receiver_key << " " << receiverBalance;

    return output.str();
}

Block Serializer::deserializeBlock(string blockStr) {
    string prevBHash;
    vector<Transaction> storedTransactions;
    string timestamp;
    float version;
    int nonce;
    int diffTarget;

    stringstream input(blockStr);
    input >> prevBHash >> timestamp >> version >> nonce >> diffTarget;
    while(!input.eof()){
        string transactionStr;
        for(int i = 0; i < 8; i++){ // 8/transaction
            string anything;
            input >> anything;
            if(!anything.empty()){
                transactionStr += anything;
                transactionStr += " ";
            }
        }

        if(!transactionStr.empty() || (transactionStr.find_first_not_of(' ') != std::string::npos)){
            cout << "Transaction: " << transactionStr << endl << endl;
            Transaction t = deserializeTransaction(transactionStr);
            storedTransactions.push_back(t);
        }
    }
    return Block(storedTransactions, prevBHash, timestamp, version, diffTarget, nonce);
}

string Serializer::serializeBlock(Block &block) {

    string prevBHash = block.getPrevBlockHash();
    vector<Transaction> storedTransactions = block.getTransactionsInBlock();
    string timestamp = block.getTimeStamp();
    float version = block.getBlockVersion();
    int nonce = block.getNonce();
    int diffTarget = block.getDiffTarget();

    stringstream output;
    output << prevBHash << " " << timestamp << " " << version << " " << nonce << " " << diffTarget << " ";
    for(Transaction& t : storedTransactions){
        output << serializeTransaction(t) << " ";
    }

    return output.str();
}


