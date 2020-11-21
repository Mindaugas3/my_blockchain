//
// Created by Mindaugas on 2020-11-06.
//
#pragma once
#ifndef BLOCKCHN_USER_H
#define BLOCKCHN_USER_H

#include <string>


using namespace std;

class User {
    private:
        string uName = "";
        string publicKey = "";
        float bal{};
    public:
        User(const string& name);
        User(const string& name, const string& pkey, float balance);
        User(const User& user);
        string getName() const ;
        float getBalance() const ;
        string getKey() const;
        void addBalance(float f);
        bool operator==(User u);
        User& operator=(const User& u);
        ~User() = default;
};
#endif //BLOCKCHN_USER_H