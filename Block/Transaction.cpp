//
// Created by Mindaugas on 2020-11-06.
//

#include "Transaction.h"

#include <cmath>
#include "../Generators/hashes/Hash_Generator.h"
#define EPSILON 1

Transaction::Transaction(User _sender,User _receiver, float _amount)
        : receiver(receiver), sender(sender) {
    amount = _amount;
    sender = _sender;
    receiver = _receiver;
    //hashas
    transactionHash = Hash_Generator(to_string(amount) + _sender.getKey() + _receiver.getKey()).getHash();
}

string Transaction::getHash() const{
    return this->transactionHash;
}

User Transaction::getSender() {
    return this->sender;
}

User Transaction::getReceiver() {
    return this->receiver;
}

float Transaction::getAmount() {
    return this->amount;
}

Transaction::Transaction(const Transaction &transaction, User receiver, User sender)
        : receiver(receiver), sender(sender) {
    amount = transaction.amount;
    sender = transaction.sender;
    receiver = transaction.receiver;
    transactionHash = transaction.transactionHash;
}

bool Transaction::operator==(Transaction transaction) {
    return this->sender == transaction.getSender() and //AND
    this->transactionHash == transaction.getHash() and //AND
    this->receiver == transaction.getReceiver() and //AND
    User::FloatApproximatelyEquals(this->amount, transaction.getAmount());
}

Transaction::~Transaction() = default;
