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

template <typename T>
void getValidInput(const std::string& prompt, T& value, T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max()) {
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < min || value > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input."<<std::endl;
        }
        else {
            break;
        }
    }
}

int main() {
    int choice;
    double S, K, r, sigma, T, up,down;
    int steps;


    while (true) {
        displayMenu();
        getValidInput("", choice, 1, 4);
        if (choice == 4) break;

        getValidInput("Enter underlying price (S): ", S);
        getValidInput("Enter strike price (K): ", K);
        getValidInput("Enter risk-free rate (r): ", r);
        getValidInput("Enter volatility (sigma): ", sigma);
        getValidInput("Enter time to maturity (T in years): ", T);

        CallOption callOption(K, T);
        PutOption putOption(K, T);

        switch (choice) {
        case 1: { // CRR
            std::cout << "\nChoose your Option type" << std::endl;
            std::cout << "1. European Vanilla" << std::endl;
            std::cout << "2. American" << std::endl;
            std::cout << "3. Digital" << std::endl;
            getValidInput("Enter your choice: ", choice,1,3);
            
            if (choice == 1)
            {
                
                CallOption callOption(T,K);
                PutOption putOption(T,K);
                getValidInput("Enter number of steps: ", steps);
                getValidInput("Enter Up value: ", up);
                getValidInput("Enter Down value: ", down);
                
                CRRPricer crrCall(&callOption, steps, S,up,down, r);
                CRRPricer crrPut(&putOption, steps, S,up,down, r);
                std::cout << "CRR European Vanilla Call Price: " << crrCall() << std::endl;
                std::cout << "CRR European Vanilla Put Price: " << crrPut() << std::endl;

            }
            else if (choice == 2)
            {
                
                AmericanCallOption callOption(T,K);
                AmericanPutOption putOption(T,K);
                getValidInput("Enter number of steps: ", steps);
                
                CRRPricer crrCall(&callOption, steps, S,r,sigma);
                CRRPricer crrPut(&putOption, steps, S,r,sigma);
                std::cout << "CRR American Call Price: " << crrCall() << std::endl;
                std::cout << "CRR American Put Price: " << crrPut() << std::endl;
            }
            else if (choice == 3)
            {
                
                
                
                EuropeanDigitalCallOption callOption(K, T);
                EuropeanDigitalPutOption putOption(K, T);
                getValidInput("Enter number of steps: ", steps);
                CRRPricer crrCall(&callOption, steps, S, r,sigma);
                CRRPricer crrPut(&putOption, steps, S, r,sigma);
                std::cout << "CRR European Digital Call Price: " << crrCall() << std::endl;
                std::cout << "CRR European Digital Put Price: " << crrPut() << std::endl;
            }
            break;
        }
        case 2: { // Black-Scholes
            std::cout << "\nChoose your Option type" << std::endl;
            std::cout << "1. European Vanilla" << std::endl;
            std::cout << "2. Digital" << std::endl;
            getValidInput("Enter your choice: ", choice, 1, 3);
            if (choice == 1)
            {
                CallOption callOption(T, K);
                PutOption putOption(T, K);
                BlackScholesPricer bsCall(&callOption, S, r, sigma);
                BlackScholesPricer bsPut(&putOption, S, r, sigma);
                std::cout << "Black-Scholes European Vanilla Call Price: " << bsCall() << std::endl;
                std::cout << "Black-Scholes European Vanilla Put Price: " << bsPut() << std::endl;

            }
            else if (choice == 2)
            {
                EuropeanDigitalCallOption callOption(T, K);
                EuropeanDigitalPutOption putOption(T, K);
                BlackScholesPricer bsCall(&callOption, S, r, sigma);
                BlackScholesPricer bsPut(&putOption, S, r, sigma);
                std::cout << "Black-Scholes European Digital Call Price: " << bsCall() << std::endl;
                std::cout << "Black-Scholes European Digital Put Price: " << bsPut() << std::endl;
            }
            break;
        }
        case 3: { // Monte Carlo Simulation
            int simulations;
            std::cout << "\nChoose your Option type" << std::endl;
            std::cout << "1. European Vanilla" << std::endl;
            std::cout << "2. Asian" << std::endl;
            std::cout << "3. Digital" << std::endl;
            getValidInput("Enter your choice: ", choice, 1, 3);
            
            if (choice == 1)
            {
                
                CallOption callOption(T,K);
                PutOption putOption(T,K);
                getValidInput("Enter number of simulations: ", simulations);
                
                BlackScholesMCPricer mcCall(&callOption, S, r, sigma);
                BlackScholesMCPricer mcPut(&putOption, S, r, sigma);
                mcCall.generate(simulations);
                mcPut.generate(simulations);
                std::cout << "Monte Carlo Call Price: " << mcCall() << std::endl;
                std::cout << "Monte Carlo Put Price: " << mcPut() << std::endl;

            }
            
            else if (choice == 2)
            {
                int nsteps;
                std::vector<double> _timesteps;
                getValidInput("Enter number of steps: ", nsteps);
                
                _timesteps.push_back(0);
                for (int i = 0; i <nsteps ; i++)
                {
                    _timesteps.push_back(_timesteps[i] + T/nsteps);
                }
                AsianCallOption callOption(T,_timesteps, K);
                AsianPutOption putOption(T,_timesteps, K);
                getValidInput("Enter number of simulations: ", simulations);
                BlackScholesMCPricer mcCall(&callOption, S, r, sigma);
                BlackScholesMCPricer mcPut(&putOption, S, r, sigma);
                mcCall.generate(simulations);
                mcPut.generate(simulations);
                std::cout << "Monte Carlo Call Price: " << mcCall() << std::endl;
                std::cout << "Monte Carlo Put Price: " << mcPut() << std::endl;
            }
            else if (choice == 3)
            {
                EuropeanDigitalCallOption callOption(T,K);
                EuropeanDigitalPutOption putOption(T,K);
                getValidInput("Enter number of simulations: ", simulations);
                BlackScholesMCPricer mcCall(&callOption, S, r, sigma);
                BlackScholesMCPricer mcPut(&putOption, S, r, sigma);
                mcCall.generate(simulations);
                mcPut.generate(simulations);
                std::cout << "Monte Carlo Call Price: " << mcCall() << std::endl;
                std::cout << "Monte Carlo Put Price: " << mcPut() << std::endl;
            }

            break;
        }
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    std::cout << "Exiting program..." << std::endl;
    return 0;
}
