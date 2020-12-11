//
// Created by Mindaugas on 2020-11-06.
//

#pragma once

#include<bitcoin/bitcoin.hpp>
#include "../Block/Transaction.h"
#include <vector>

class TransactionGenerator {
    public:
        static vector<Transaction> pickFromUsers(vector<User> users, int number);
	static bc::hash_digest create_merkle(bc::hash_list& merkle);
        static string getMerkleRoot(const vector<Transaction>& transactionPool);
};
