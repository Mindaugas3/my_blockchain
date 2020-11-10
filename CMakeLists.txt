cmake_minimum_required(VERSION 3.16)
project(blockchn)

set(CMAKE_CXX_STANDARD 14)

add_executable(blockchn main.cpp Generators/hashes/Hash_Generator.cpp Generators/hashes/Hash_Generator.h Generators/TransactionGenerator.cpp Generators/TransactionGenerator.h Block/Block.cpp Block/Block.h Generators/UserGenerator.cpp Generators/UserGenerator.h Block/User.cpp Block/User.h Block/Transaction.cpp Block/Transaction.h Generators/RNG.cpp Generators/RNG.h Generators/Miner.cpp Generators/Miner.h Generators/hashes/Sha256.cpp Generators/hashes/Sha256.h Block/CandidateBlock.cpp Block/CandidateBlock.h Generators/VerifyTransaction.cpp Generators/VerifyTransaction.h)