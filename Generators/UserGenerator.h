//
// Created by Mindaugas on 2020-11-06.
//
#pragma once
#ifndef BLOCKCHN_USERGENERATOR_H
#define BLOCKCHN_USERGENERATOR_H

#include <vector>
#include "../Block/User.h"



using namespace std;

class UserGenerator {
    public:
        static void generateUsers(vector<User>& userV, int amount);
};
#endif //BLOCKCHN_USERGENERATOR_H