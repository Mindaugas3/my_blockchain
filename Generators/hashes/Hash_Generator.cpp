//
// Created by Mindaugas on 2020-11-06.
//

#include "Hash_Generator.h"
#include <stdexcept>
#include <chrono>
#include <ios>
#include <sstream>

vector<byte> Hash_Generator::getOutput() {
    return output;
}

string Hash_Generator::getHash(){
    std::stringstream Q;
    for(uint8_t a : this->output){
        Q << std::hex << static_cast<int>(a);
    }
    return Q.str();
}

Hash_Generator::Hash_Generator(string str) {

    vector<byte> v;

    unsigned int index = 0;

    for(auto it = str.begin(); it < str.end(); ++it){
        v.push_back(operations(*it, valuesList[index]));

        if(index == max_index){
            index = 0;
        } else {
            index++;
        }
    }

    vector<byte> bytevec = TrimAndFill(v);
    output = bytevec;
}


vector<byte> Hash_Generator::TrimAndFill(vector<byte> ivec){

    vector<byte> r_vec(DEFAULT_HASH_LENGTH); //tuscias
    size_t inputSize = ivec.size();

    for(int i = 0; i < r_vec.size(); i++){
        r_vec[i] = valuesList[i % max_index]; //pasikartojanti seka
        //uzpildo tuscia vektoriu su reiksmemis
    }

    auto forwardIterator = r_vec.begin();
    int valIndex = 0;

    unsigned long long bytesSum = addAll(ivec);

    if(inputSize > DEFAULT_HASH_LENGTH){ //musu inputas ilgesnis uz hasho ilgi
        for(auto X = ivec.begin(); X < ivec.end(); X++) {
            if (forwardIterator < r_vec.end()) {
                //pildome
                *X ^= bytesSum;
                *forwardIterator ^= (*X >> 3u);
                *forwardIterator += operations(*X, valIndex);
                ++forwardIterator;
            } else {
                //nukreipiame pointeri i pati pirma iteratoriu
                valIndex = 0;
                forwardIterator = r_vec.begin();
            }
            ++valIndex;
        }
        //dalis apacioje neuzims daug laiko
    } else { //musu inputas ir hashas yra vienodo ilgio arba inputas trumpesnis
        auto inputIterator = ivec.begin();
        for(auto B = r_vec.begin(); B < r_vec.end(); ++B){
            if(inputIterator < ivec.end()){
                //sniego lavinos ciklas
                *B ^= bytesSum;
                *B += operations(*inputIterator, valIndex);
                *B <<= 3u;
                *B ^= *inputIterator;
                ++inputIterator;
            } else {
                //nukreipiame pointeri i pati pirma inputo iteratoriu
                inputIterator = ivec.begin();
            }
            ++valIndex;
        }
    }

    return r_vec;
}


byte Hash_Generator::operations(byte item, byte val){
    //AND, XOR, NOT,
    byte item_ = item;
    //1 etapas
    item_ = rrot(item, val);
    item_ ^= item;
    //
    item_ = rshift(item_, 5);
    item_ |= flip(item);
    item_ = lrot(item_, 3);
    return item_;
}



Hash_Generator::Hash_Generator(const Hash_Generator& conv) {
    this->output = conv.output;
}

unsigned long long int Hash_Generator::addAll(vector<byte> items) {
    unsigned long long int value = 0;
    for(byte b : items){
        value += (int) b;
    }
    return value;
}

byte Hash_Generator::rshift(byte item, byte amount) {
    return (item >> amount);
}

byte Hash_Generator::rrot(byte item, byte amount) {
    return (item >> amount) | (item << (-amount & 7));
}

byte Hash_Generator::lshift(byte item, byte amount) {
    return (item << amount);
}

byte Hash_Generator::lrot(byte item, byte amount) {
    return (item << amount) | (item >> (-amount & 7));
}

byte Hash_Generator::XOR(byte item, byte value) {
    return item ^ value;
}

byte Hash_Generator::flip(byte item) {
    return ~item;
}

byte Hash_Generator::AND(byte item, byte value) {
    return item + value;
}


Hash_Generator& Hash_Generator::operator=(const Hash_Generator &conv) = default;

Hash_Generator::~Hash_Generator() = default;
