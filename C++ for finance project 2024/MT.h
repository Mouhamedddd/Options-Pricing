#pragma once

#include <random>
#include <mutex>

class MT
{
private:
    // a private membber to gold the rdm number generator
    std::mt19937 rng;

    // we crerate a prive cosntrcutor to initialises the rng with a rdom seeed
    MT();

    // we delete copy constructor and assignment operator
    MT(const MT&) = delete;
    MT& operator=(const MT&) = delete;

    // static instance pointer ++ mutex for thread safety
    static MT* instance;
    static std::mutex mtx;

public:
    //pblicc static method to get the singleton instance
    static MT* getInstance();

    // to generatee a uniform random number in [0, 1]
    double rand_unif();

    //in order to generate a normal random number with mean 0 and standard deviation 1
    double rand_norm();

    // dstructor
    ~MT();
};

