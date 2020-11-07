//
// Created by Mindaugas on 2020-11-06.
//

#ifndef BLOCKCHN_USER_H
#define BLOCKCHN_USER_H

#include <string>

using namespace std;

class User {
    private:
        string uName;
        string publicKey;
        string privateKey;
        float bal;
    public:
        explicit User(string name);
        string getName();
        float getBalance();
        string getKey();
};
#endif //BLOCKCHN_USER_H