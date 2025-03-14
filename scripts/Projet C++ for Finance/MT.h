#pragma once

#include <random>
#include <mutex>

class MT
{
private:
    // Private member to hold the random number generator
    std::mt19937 rng;

    // Private constructor initializes the RNG with a random seed
    MT();

    // Delete copy constructor and assignment operator
    MT(const MT&) = delete;
    MT& operator=(const MT&) = delete;

    // Static instance pointer and mutex for thread safety
    static MT* instance;
    static std::mutex mtx;

public:
    // Public static method to get the singleton instance
    static MT* getInstance();

    // Generate a uniform random number in [0, 1]
    double rand_unif();

    // Generate a normal random number with mean 0 and standard deviation 1
    double rand_norm();

    // Destructor
    ~MT();
};

