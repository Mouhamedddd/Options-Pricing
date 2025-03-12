#include "MT.h"

#include "MT.h"

// we initialize statics membersd
MT* MT::instance = nullptr;
std::mutex MT::mtx;

//private cstructor
MT::MT() : rng(std::random_device{}()) {}

// destructor
MT::~MT() = default;

//to get singleton instance
MT* MT::getInstance() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!instance) {
        instance = new MT();
    }
    return instance;
}

// create a fction to generate a uniform random number( in [0, 1]))
double MT::rand_unif() {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(rng);
}

// we create a fnction to generate  a normal random number ((with mean 0 and standard deviation 1))
double MT::rand_norm() {
    std::normal_distribution<double> dist(0.0, 1.0);
    return dist(rng);
}
