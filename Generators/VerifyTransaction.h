//
// Created by Mindaugas on 2020-11-10.
//
#pragma once
#ifndef BLOCKCHN_VERIFYTRANSACTION_H
#define BLOCKCHN_VERIFYTRANSACTION_H

#include "../Block/Transaction.h"

class VerifyTransaction{
public:
    static bool verify(Transaction& t);

    static bool senderHasEnoughCredits(Transaction& transaction);
};


#endif //BLOCKCHN_VERIFYTRANSACTION_H
