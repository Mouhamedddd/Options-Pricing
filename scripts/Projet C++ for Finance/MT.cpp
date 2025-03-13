#include "MT.h"

#include "MT.h"

// Initialize static members
MT* MT::instance = nullptr;
std::mutex MT::mtx;

// Private constructor
MT::MT() : rng(std::random_device{}()) {}

// Destructor
MT::~MT() = default;

// Get the singleton instance (thread-safe)
MT* MT::getInstance() {
    std::lock_guard<std::mutex> lock(mtx); // Thread-safe initialization
    if (!instance) {
        instance = new MT();
    }
    return instance;
}

// Generate a uniform random number in [0, 1]
double MT::rand_unif() {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(rng);
}

// Generate a normal random number with mean 0 and standard deviation 1
double MT::rand_norm() {
    std::normal_distribution<double> dist(0.0, 1.0);
    return dist(rng);
}
