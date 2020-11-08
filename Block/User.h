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
        User() = default;
        explicit User(string name);
        User(const User& user);
        string getName() const ;
        float getBalance() const ;
        string getKey() const;
        void addBalance(float f);
        bool operator==(User u);
};
#endif //BLOCKCHN_USER_H