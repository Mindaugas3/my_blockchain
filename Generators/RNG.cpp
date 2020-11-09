//
// Created by Mindaugas on 2020-11-08.
//

#include "RNG.h"
#include <random>
#include <ctime>
#include <chrono>

using namespace std;
int RNG::rangeRandom (int min, int max){
    srand(time(NULL));
    std::mt19937 mt(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> dist(min, max);
    return dist(mt);
}
