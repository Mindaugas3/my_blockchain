//
// Created by Mindaugas on 2020-11-06.
//

#include "Transaction.h"
#include "../Generators/hashes/Hash_Generator.h"

Transaction::Transaction(const User& _sender, const User& _receiver, float _amount) {
    this->amount = _amount;
    this->sender = _sender;
    this->receiver = _receiver;
    //hashas
    this->transactionHash = Hash_Generator(to_string(amount) + _sender.getKey() + _receiver.getKey()).getHash();
}

string Transaction::getHash() {
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
