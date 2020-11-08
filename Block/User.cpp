//
// Created by Mindaugas on 2020-11-06.
//

#include "User.h"
#include "../Generators/RNG.h"
#include "../Generators/hashes/Hash_Generator.h"

User::User(string name) {
    this->uName = name;
    this->bal = RNG::rangeRandom(100, 1000000);
    this->publicKey = "";
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

User::User(const User &user) {

}
