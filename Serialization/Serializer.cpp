//
// Created by Mindaugas on 2020-11-21.
//

#include <iostream>
#include <iomanip>
#include "Serializer.h"

Transaction Serializer::deserializeTransaction(const string& transactionStr) {
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

Block Serializer::deserializeBlock(const string& blockStr, const vector<Transaction>& trVec) {
    string prevBHash;
    string timestamp;
    float version;
    int nonce;
    int diffTarget;

    stringstream input(blockStr);
    input >> prevBHash >> timestamp >> version >> nonce >> diffTarget;


    cout << "Returning block!" << endl;
    return Block(trVec, prevBHash, timestamp, version, diffTarget, nonce);
}

string Serializer::serializeBlock(Block &block) {

    string prevBHash = block.getPrevBlockHash();
    string timestamp = block.getTimeStamp();
    float version = block.getBlockVersion();
    int nonce = block.getNonce();
    int diffTarget = block.getDiffTarget();

    stringstream output;
    output << prevBHash << " " << timestamp << " " << version << " " << nonce << " " << diffTarget << " ";

    return output.str();
}


