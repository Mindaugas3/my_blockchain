//
// Created by Mindaugas on 2020-11-06.
//

#include "User.h"

User::User(string name) {
    this->uName = name;

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
