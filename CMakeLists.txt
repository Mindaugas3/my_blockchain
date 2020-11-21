cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)

project(blockchn)

# Require MPI for this project:
if(WIN32 OR WIN64)
    #This is for finding MS-MPI.
    if(WIN64)
        MESSAGE(OS NAME -> WIN64)
    else()
        MESSAGE(OS NAME -> WIN32)
    endif()

    set(_MPI_PREFIX_PATH)
    list(APPEND _MPI_PREFIX_PATH "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\MPI;Path]/..")
    set(MPIEXEC "C:/Program Files/Microsoft MPI/Bin/mpiexec.exe")
    # For building MPI programs the selected Visual Studio compiler is used, namely cl.exe.
    # So there is no need to set a specific MPI compiler.
    set(MPI_CXX_INCLUDE_PATH "C:/Program Files (x86)/Microsoft SDKs/MPI/Include")
    # Make sure the correct libraries (64-bit or 32-bit) are selected.
    # Decide between 32-bit and 64-bit libraries for Microsoft's MPI
    if("${CMAKE_SIZEOF_VOID_P}" EQUAL 8)
        set(MS_MPI_ARCH_DIR x64)
    else()
        set(MS_MPI_ARCH_DIR x86)
    endif()
    set(MPI_CXX_LIBRARIES "C:/Program Files (x86)/Microsoft SDKs/MPI/Lib/${MS_MPI_ARCH_DIR}/msmpi.lib")
    set(MPI_C_INCLUDE_PATH "${MPI_CXX_INCLUDE_PATH}") #c -> cxx
    set(MPI_C_LIBRARIES "${MPI_CXX_LIBRARIES}")#c -> cxx
    set(MPIEXEC_NUMPROC_FLAG "-n" CACHE STRING "Flag used by MPI to specify the number of processes for MPIEXEC; the next option will be the number of processes.")
else()
    find_package(MPI REQUIRED)
endif()

set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_CXX_COMPILE_FLAGS})
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_CXX_LINK_FLAGS})
include_directories(${MPI_CXX_INCLUDE_PATH})
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(${PROJECT_NAME} main.cpp Block/User.cpp Block/User.h Block/Transaction.cpp Block/Transaction.h
        Generators/Miner.cpp Generators/Miner.h Generators/RNG.cpp Generators/RNG.h Generators/TransactionGenerator.cpp Generators/TransactionGenerator.h
        Generators/UserGenerator.cpp Generators/UserGenerator.h Generators/VerifyTransaction.cpp Generators/VerifyTransaction.h
        Generators/hashes/Hash_Generator.cpp Generators/hashes/Hash_Generator.h Generators/hashes/Sha256.cpp Generators/hashes/Sha256.h
        Block/Block.cpp Block/Block.h Serialization/Serializer.cpp Serialization/Serializer.h)

target_link_libraries(${PROJECT_NAME} ${MPI_CXX_LIBRARIES})

# Add a test:
enable_testing()
if(WIN32 OR WIN64)
    add_test(SimpleTest ${MPIEXEC} -debug 2 ${MPIEXEC_NUMPROC_FLAG} 6 ${CMAKE_CURRENT_BINARY_DIR}/debug/${PROJECT_NAME}.exe)
else()
    add_test(SimpleTest ${MPIEXEC} -debug 2 ${MPIEXEC_NUMPROC_FLAG} 6 ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME})
endif()
