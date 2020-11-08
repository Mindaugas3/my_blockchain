//
// Created by Mindaugas on 2020-11-06.
//

#include "User.h"
#include "../Generators/RNG.h"
#include "../Generators/hashes/Hash_Generator.h"

User::User(string name) {
    this->uName = name;
    this->bal = RNG::rangeRandom(100, 1000000);
    Hash_Generator hgen = Hash_Generator(name);
    this->publicKey = hgen.getHash();
}

string User::getName() const{
    return this->uName;
}

float User::getBalance() const{
    return this->bal;
}

string User::getKey() const{
    return this->publicKey;
}

User::User(const User &user) {
    this->uName = user.getName();
    this->publicKey = user.getKey();
    this->bal = user.getBalance();
}
