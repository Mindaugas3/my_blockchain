//
// Created by Mindaugas on 2020-11-21.
//

#include "Serializer.h"

Transaction Serializer::TransactionFromString(string transactionStr) {
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

string Serializer::TransactionToString(Transaction& transaction) {
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
    output << hash << " " << amount << " "
    << senderName << " " << sender_key << " " << senderBalance << " "
    << receiverName << " " << receiver_key << " " << receiverBalance;

    return output.str();
}
