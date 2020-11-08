#include <iostream>
#include <vector>
#include <string>
#include "Block/User.h"
#include "Generators/UserGenerator.h"

int main() {
    vector<User> users = UserGenerator::generateUsers(1000); //nauji useriai


    return 0;
}
