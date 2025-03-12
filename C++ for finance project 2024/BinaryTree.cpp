#include "BinaryTree.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
// constructor
template <typename T>
BinaryTree<T>::BinaryTree(int depth) {
    _depth = depth;
    _tree.resize(_depth + 1);
    for (int i = 0; i < _tree.size(); i++)
        _tree[i].resize(i + 1);
}

//Destructor
template <typename T>
BinaryTree<T>::~BinaryTree() {}

//to get the depth of the tree
template<typename T>
int BinaryTree<T>::getDepth() {
    return _depth;
}
template<typename T>
void BinaryTree<T>::setDepth(int depth) {
    _depth = depth;
    _tree.resize(_depth + 1);  ///resizes the outer vector
    for (int i = 0; i <= _depth; ++i) {
        _tree[i].resize(i + 1);  // resizes each inner vector
    }
}

// sdetter for a node value
template<typename T>

void BinaryTree<T>::setNode(int n, int i, T value) {
    if (n >= 0 && n <= _depth && i >= 0 && i <= n) {
        _tree[n][i] = value;
    }
    else {
        std::cerr << "Invalid node indices\n";
    }
}

template<typename T>
T BinaryTree<T>::getNode(int n, int i) const {
    if (n >= 0 && n <= _depth && i >= 0 && i <= n) {
        return _tree[n][i];
    }
    throw std::out_of_range("Invalid node indices");
}

// method to display the tree in a precise triangular form
template<typename T>
void BinaryTree<T>::display()
{
    //firstt representation : level by level (aligned form)
    for (int level = 0; level <= _depth; ++level)
    {
        for (int idx = 0; idx <= level; ++idx)
        {
            //we display each node value in the current level
            std::cout << _tree[level][idx];
            if (idx != level)
            {
                //we add a tab space in the same level:
                std::cout << "\t";
            }
        }
        std::cout << std::endl;
        //We have completed the level
    }

    //we separate the two levels for clarity
    std::cout << std::endl;

    // Second representation triang form
    for (size_t i = 0; i < _tree.size(); ++i)
    {
        //We calcualte the current padding to center a current level
        int padding = (_depth - i) * 3 + 3;

        //
        for (int k = 0; k < padding; ++k)
        {
            std::cout << " ";
        }

        // print of actual leel
        for (size_t j = 0; j < _tree[i].size(); ++j)
        {
            long valueLength = 0;
            if (static_cast<int>(_tree[i][j]) == _tree[i][j])
            {
                //in the case where the value is an integer, we claclate its lenght directly to align it properlt
                valueLength = std::to_string(static_cast<int>(_tree[i][j])).length();
            }
            else
            {
                //else we scale it and calculate length with decimal
                valueLength = std::to_string(static_cast<int>(_tree[i][j] * 100)).length() + 1;
            }
            //we adjust then depnding o nthe value
            if (valueLength <= 2)
            {
                std::cout << "  " << _tree[i][j] << "   ";
            }
            else if (valueLength == 3)
            {
                std::cout << " " << _tree[i][j] << "  ";
            }
            else
            {


                std::cout << _tree[i][j] << "  ";
            }
        }
        std::cout << std::endl;

        //to display connectors
        if (i < _tree.size() - 1)
        {
            for (int k = 0; k < padding; ++k)
            {
                std::cout << " ";
            }

            for (size_t j = 0; j < _tree[i].size(); ++j)
            {
                std::cout << "/   \\ ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}



// modl function for each types
template class BinaryTree<bool>;
template class BinaryTree<double>;
template class BinaryTree<int>;