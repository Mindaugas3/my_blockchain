//
// Created by Mindaugas on 2020-11-10.
//

#include "VerifyTransaction.h"
#include "hashes/Hash_Generator.h"

bool VerifyTransaction::verify(Transaction& t){
    //transakcijos hashas
        float bal = t.getAmount();
        string senderKey = t.getSender().getKey();
        string receiverKey = t.getReceiver().getKey();
        return (t.getHash() == Hash_Generator(to_string(bal) + senderKey + receiverKey).getHash());
}
