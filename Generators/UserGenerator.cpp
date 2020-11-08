//
// Created by Mindaugas on 2020-11-06.
//

#include "UserGenerator.h"

vector<User> UserGenerator::generateUsers(int amount) {
    vector<User> users = vector<User>();
    for(int i = 0; i< amount; i++){

        User someUser = User("user"+to_string(i));
        users.push_back(someUser);
        amount--;
    }
    return users;
}
