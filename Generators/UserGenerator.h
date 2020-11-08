//
// Created by Mindaugas on 2020-11-06.
//

#ifndef BLOCKCHN_USERGENERATOR_H
#define BLOCKCHN_USERGENERATOR_H

#include <vector>
#include "../Block/User.h"

#endif //BLOCKCHN_USERGENERATOR_H

using namespace std;

class UserGenerator {
    public:
        static vector<User> generateUsers(int amount);
};