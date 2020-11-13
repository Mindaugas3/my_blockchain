//
// Created by Mindaugas on 2020-11-06.
//

#include "UserGenerator.h"
#include <omp.h>

void UserGenerator::generateUsers(vector<User>& userVec, int amount) {
#pragma omp parallel for
    for(int i = 0; i< amount; i++){

        User someUser = User("user"+to_string(i));
        userVec.push_back(someUser);
    }
}
