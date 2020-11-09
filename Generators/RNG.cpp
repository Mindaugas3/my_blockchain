//
// Created by Mindaugas on 2020-11-08.
//

#include "RNG.h"
#include <random>
#include <ctime>
    using namespace std;
int RNG::rangeRandom (int min, int max){
    srand(time(NULL));
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(min, max);
    return dist(mt);
}
