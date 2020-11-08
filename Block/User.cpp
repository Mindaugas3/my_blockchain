//
// Created by Mindaugas on 2020-11-06.
//

#include "User.h"
#include "../Generators/RNG.h"

User::User(string name) {
    this->uName = name;
    this->bal = RNG::rangeRandom(100, 10000000);
    
}

string User::getName() {
    return this->uName;
}

float User::getBalance() {
    return this->bal;
}

string User::getKey() {
    return this->publicKey;
}
