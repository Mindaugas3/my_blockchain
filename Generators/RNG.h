//
// Created by Mindaugas on 2020-11-08.
//
#pragma once
#ifndef BLOCKCHN_RNG_H
#define BLOCKCHN_RNG_H
#include <cstdlib>


class RNG {
    public:
        static int rangeRandom(int min, int max);
};
#endif //BLOCKCHN_RNG_H