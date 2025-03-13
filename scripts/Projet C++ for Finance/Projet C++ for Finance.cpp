#include <iostream>
#include "BlackScholesPricer.h"
#include "CRRPricer.h"
#include "Option.h"
#include "CallOption.h"
#include "PutOption.h"
#include "AmericanCallOption.h"
#include "AmericanPutOption.h"
#include "AsianCallOption.h"
#include "AsianPutOption.h"
#include "EuropeanDigitalCallOption.h"
#include "EuropeanDigitalPutOption.h"
#include "BlackScholesMCPricer.h"

void displayMenu() {
    std::cout << "\nOption Pricing Menu" << std::endl;
    std::cout << "1. Price option using CRR Binomial Tree" << std::endl;
    std::cout << "2. Price option using Black-Scholes" << std::endl;
    std::cout << "3. Price option using Monte Carlo Simulation" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}



int main() {
    int choice;
    double S, K, r, sigma, T, up,down;
    int steps;

    while (true) {
        displayMenu();
        std::cin >> choice;
        if (choice == 4) break;

        std::cout << "Enter underlying price (S): ";
        std::cin >> S;
        std::cout << "Enter strike price (K): ";
        std::cin >> K;
        std::cout << "Enter risk-free rate (r): ";
        std::cin >> r;
        std::cout << "Enter volatility (sigma): ";
        std::cin >> sigma;
        std::cout << "Enter time to maturity (T in years): ";
        std::cin >> T;

        CallOption callOption(K, T);
        PutOption putOption(K, T);

        switch (choice) {
        case 1: { // CRR
            std::cout << "\nChoose your Option type" << std::endl;
            std::cout << "1. European Vanilla" << std::endl;
            std::cout << "2. American" << std::endl;
            std::cout << "3. Digital" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            if (choice == 1)
            {
                std::cout << "Enter underlying price (S): ";
                std::cin >> S;
                std::cout << "Enter strike price (K): ";
                std::cin >> K;
                std::cout << "Enter risk-free rate (r): ";
                std::cin >> r;
                std::cout << "Enter volatility (sigma): ";
                std::cin >> sigma;
                std::cout << "Enter time to maturity (T in years): ";
                std::cin >> T;
                CallOption callOption(K, T);
                PutOption putOption(K, T);
                std::cout << "Enter number of steps: ";
                std::cin >> steps;
                CRRPricer crrCall(&callOption, steps, S, r, sigma);
                CRRPricer crrPut(&putOption, steps, S, r, sigma);
                std::cout << "CRR European Vanilla Call Price: " << crrCall() << std::endl;
                std::cout << "CRR European Vanilla Put Price: " << crrPut() << std::endl;

            }
            else if (choice == 2)
            {
                std::cout << "Enter underlying price (S): ";
                std::cin >> S;
                std::cout << "Enter strike price (K): ";
                std::cin >> K;
                std::cout << "Enter risk-free rate (r): ";
                std::cin >> r;
                std::cout << "Enter volatility (sigma): ";
                std::cin >> sigma;
                std::cout << "Enter time to maturity (T in years): ";
                std::cin >> T;
                AmericanCallOption callOption(K, T);
                AmericanPutOption putOption(K, T);
                std::cout << "Enter number of steps: ";
                std::cin >> steps;
                CRRPricer crrCall(&callOption, steps, S, r, sigma);
                CRRPricer crrPut(&putOption, steps, S, r, sigma);
                std::cout << "CRR American Call Price: " << crrCall() << std::endl;
                std::cout << "CRR American Put Price: " << crrPut() << std::endl;
            }
            else if (choice == 3)
            {
                std::cout << "Enter underlying price (S): ";
                std::cin >> S;
                std::cout << "Enter strike price (K): ";
                std::cin >> K;
                std::cout << "Enter risk-free rate (r): ";
                std::cin >> r;
                std::cout << "Enter Up value: ";
                std::cin >> up;
                std::cout << "Enter Down value: ";
                std::cin >> down;
                std::cout << "Enter time to maturity (T in years): ";
                std::cin >> T;
                EuropeanDigitalCallOption callOption(K, T);
                EuropeanDigitalPutOption putOption(K, T);
                std::cout << "Enter number of steps: ";
                std::cin >> steps;
                CRRPricer crrCall(&callOption, steps, S, up, down, r);
                CRRPricer crrPut(&putOption, steps, S, up, down, r);
                std::cout << "CRR European Digital Call Price: " << crrCall() << std::endl;
                std::cout << "CRR European Digital Put Price: " << crrPut() << std::endl;
            }
            break;
        }
        case 2: { // Black-Scholes
            std::cout << "\nChoose your Option type" << std::endl;
            std::cout << "1. European Vanilla" << std::endl;
            std::cout << "2. Digital" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            if (choice == 1)
            {
                std::cout << "Enter underlying price (S): ";
                std::cin >> S;
                std::cout << "Enter strike price (K): ";
                std::cin >> K;
                std::cout << "Enter risk-free rate (r): ";
                std::cin >> r;
                std::cout << "Enter volatility (sigma): ";
                std::cin >> sigma;
                std::cout << "Enter time to maturity (T in years): ";
                std::cin >> T;
                CallOption callOption(K, T);
                PutOption putOption(K, T);
                BlackScholesPricer bsCall(&callOption, S, r, sigma);
                BlackScholesPricer bsPut(&putOption, S, r, sigma);
                std::cout << "Black-Scholes European Vanilla Call Price: " << bsCall() << std::endl;
                std::cout << "Black-Scholes European Vanilla Put Price: " << bsPut() << std::endl;

            }
            else if (choice == 2)
            {
                std::cout << "Enter underlying price (S): ";
                std::cin >> S;
                std::cout << "Enter strike price (K): ";
                std::cin >> K;
                std::cout << "Enter risk-free rate (r): ";
                std::cin >> r;
                std::cout << "Enter volatility (sigma): ";
                std::cin >> sigma;
                std::cout << "Enter time to maturity (T in years): ";
                std::cin >> T;
                EuropeanDigitalCallOption callOption(K, T);
                EuropeanDigitalPutOption putOption(K, T);
                BlackScholesPricer bsCall(&callOption, S, r, sigma);
                BlackScholesPricer bsPut(&putOption, S, r, sigma);
                std::cout << "Black-Scholes European Digital Call Price: " << bsCall() << std::endl;
                std::cout << "Black-Scholes European Digital Put Price: " << bsPut() << std::endl;
            }
            break;
        }
        case 3: { // Monte Carlo Simulation
            std::cout << "\nChoose your Option type" << std::endl;
            std::cout << "1. European Vanilla" << std::endl;
            std::cout << "2. Asian" << std::endl;
            std::cout << "3. Digital" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            if (choice == 1)
            {
                std::cout << "Enter underlying price (S): ";
                std::cin >> S;
                std::cout << "Enter strike price (K): ";
                std::cin >> K;
                std::cout << "Enter risk-free rate (r): ";
                std::cin >> r;
                std::cout << "Enter volatility (sigma): ";
                std::cin >> sigma;
                std::cout << "Enter time to maturity (T in years): ";
                std::cin >> T;
                CallOption callOption(K, T);
                PutOption putOption(K, T);
                std::cout << "Enter number of steps: ";
                std::cin >> steps;
                CRRPricer crrCall(&callOption, steps, S, r, sigma);
                CRRPricer crrPut(&putOption, steps, S, r, sigma);
                std::cout << "CRR European Vanilla Call Price: " << crrCall() << std::endl;
                std::cout << "CRR European Vanilla Put Price: " << crrPut() << std::endl;

            }
            else if (choice == 2)
            {
                std::cout << "Enter underlying price (S): ";
                std::cin >> S;
                std::cout << "Enter strike price (K): ";
                std::cin >> K;
                std::cout << "Enter risk-free rate (r): ";
                std::cin >> r;
                std::cout << "Enter volatility (sigma): ";
                std::cin >> sigma;
                std::cout << "Enter time to maturity (T in years): ";
                std::cin >> T;
                AmericanCallOption callOption(K, T);
                AmericanPutOption putOption(K, T);
                std::cout << "Enter number of steps: ";
                std::cin >> steps;
                CRRPricer crrCall(&callOption, steps, S, r, sigma);
                CRRPricer crrPut(&putOption, steps, S, r, sigma);
                std::cout << "CRR American Call Price: " << crrCall() << std::endl;
                std::cout << "CRR American Put Price: " << crrPut() << std::endl;
            }
            else if (choice == 3)
            {
                std::cout << "Enter underlying price (S): ";
                std::cin >> S;
                std::cout << "Enter strike price (K): ";
                std::cin >> K;
                std::cout << "Enter risk-free rate (r): ";
                std::cin >> r;
                std::cout << "Enter Up value: ";
                std::cin >> T;
                EuropeanDigitalCallOption callOption(K, T);
                EuropeanDigitalPutOption putOption(K, T);
                std::cout << "Enter number of steps: ";
                std::cin >> steps;
                CRRPricer crrCall(&callOption, steps, S, up, down, r);
                CRRPricer crrPut(&putOption, steps, S, up, down, r);
                std::cout << "CRR European Digital Call Price: " << crrCall() << std::endl;
                std::cout << "CRR European Digital Put Price: " << crrPut() << std::endl;

                int simulations;
                int nsteps;
                std::vector<double> _timesteps;
                std::cout << "Enter the number of steps: ";
                std::cin >> nsteps;
                _timesteps.push_back(0);
                for (int i = 0; i <nsteps ; i++)
                {
                    _timesteps.push_back(_timesteps[i] + T/nsteps);
                }
                AsianCallOption callOption(_timesteps, T);
                AsianPutOption putOption(_timesteps, T);
                std::cout << "Enter number of simulations: ";
                std::cin >> simulations;
                BlackScholesMCPricer mcCall(&callOption, S, r, sigma);
                BlackScholesMCPricer mcPut(&putOption, S, r, sigma);
                std::cout << "Monte Carlo Call Price: " << mcCall() << std::endl;
                std::cout << "Monte Carlo Put Price: " << mcPut() << std::endl;
            }



            int simulations;
            std::cout << "Enter number of simulations: ";
            std::cin >> simulations;
            BlackScholesMCPricer mcCall(&callOption, S, r, sigma);
            BlackScholesMCPricer mcPut(&putOption, S, r, sigma);
            std::cout << "Monte Carlo Call Price: " << mcCall() << std::endl;
            std::cout << "Monte Carlo Put Price: " << mcPut() << std::endl;
            break;
        }
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    std::cout << "Exiting program..." << std::endl;
    return 0;
}
