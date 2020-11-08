//
// Created by Mindaugas on 2020-11-06.
//

#pragma once

#include "../Block/Transaction.h"
#include <vector>

class TransactionGenerator {
    public:
        static vector<Transaction> pickFromUsers(vector<User> users);
};
