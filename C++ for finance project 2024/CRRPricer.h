#pragma once
#include "BinaryTree.h"
#include "Option.h"
#include <stdexcept>
#include "AmericanOption.h"

class CRRPricer {
    private:
        Option* _option;
        int _depth;
        double _asset_price;
        double _up=1;
        double _down=-1;
        double _interest_rate=0;
        BinaryTree<double> _tree;
        bool computed;
        BinaryTree<bool> exercise_policy;
        double U=1, D=-1, R=0;

    public:
        // the constructor
        CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate);
        CRRPricer(Option* option, int depth, double asset_price, double r, double volatility);


        void checkArbitrageCondition(double down, double interest_rate, double up) const;

        // it is a method to compute the option tree
        void compute();

        //a geetter for H(n, i)
        double get(int n, int i) const;

        // overload operatir to return option price 
        double operator()(bool closed_form = false);

        //in orde r to display tree
        void displayTree() const;

        bool getExercise(int, int);
};