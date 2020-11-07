cmake_minimum_required(VERSION 3.16)
project(blockchn)

set(CMAKE_CXX_STANDARD 14)

add_executable(blockchn main.cpp cmake-build-debug/Generators/hashes/Hash_Generator.cpp cmake-build-debug/Generators/hashes/Hash_Generator.h cmake-build-debug/Generators/TransactionGenerator.cpp cmake-build-debug/Generators/TransactionGenerator.h cmake-build-debug/Block/Block.cpp cmake-build-debug/Block/Block.h cmake-build-debug/Generators/UserGenerator.cpp cmake-build-debug/Generators/UserGenerator.h cmake-build-debug/Block/User.cpp cmake-build-debug/Block/User.h cmake-build-debug/Block/Transaction.cpp cmake-build-debug/Block/Transaction.h cmake-build-debug/Block/MerkleTree.cpp cmake-build-debug/Block/MerkleTree.h)