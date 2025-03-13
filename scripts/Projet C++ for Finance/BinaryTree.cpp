#include "BinaryTree.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

// Constructor for the BinaryTree class template
template <typename T>
BinaryTree<T>::BinaryTree(int depth) {
    _depth = depth;  // Set the depth of the tree
    _tree.resize(_depth + 1);  // Resize the outer vector to hold each level of the tree
    for (int i = 0; i < _tree.size(); i++) {
        _tree[i].resize(i + 1);  // Resize each inner vector to match the number of nodes at that level
    }
}

// Destructor for the BinaryTree class template
template <typename T>
BinaryTree<T>::~BinaryTree() {}

// Method to get the depth of the tree
template<typename T>
int BinaryTree<T>::getDepth() {
    return _depth;  // Return the depth of the tree
}

// Setter for the depth of the tree, resizes the tree accordingly
template<typename T>
void BinaryTree<T>::setDepth(int depth) {
    _depth = depth;  // Set the new depth
    _tree.resize(_depth + 1);  // Resize the outer vector to the new depth
    for (int i = 0; i <= _depth; ++i) {
        _tree[i].resize(i + 1);  // Resize each inner vector to match the number of nodes at each level
    }
}

// Setter for a specific node's value at position (n, i) in the tree
template<typename T>
void BinaryTree<T>::setNode(int n, int i, T value) {
    if (n >= 0 && n <= _depth && i >= 0 && i <= n) {  // Validate the indices
        _tree[n][i] = value;  // Set the value at the specified node
    }
    else {
        std::cerr << "Invalid node indices\n";  // Print an error if indices are invalid
    }
}

// Getter for the value of a node at position (n, i) in the tree
template<typename T>
T BinaryTree<T>::getNode(int n, int i) const {
    if (n >= 0 && n <= _depth && i >= 0 && i <= n) {  // Validate the indices
        return _tree[n][i];  // Return the value of the specified node
    }
    throw std::out_of_range("Invalid node indices");  // Throw an exception if indices are invalid
}

// Method to display the tree in a level-by-level (aligned) form
template<typename T>
void BinaryTree<T>::display() {
    // First representation: level by level (aligned form)
    for (int level = 0; level <= _depth; ++level) {  // Loop through each level
        for (int idx = 0; idx <= level; ++idx) {  // Loop through each node at the current level
            std::cout << _tree[level][idx];  // Print the node value
            if (idx != level) {  // If not the last node in the level
                std::cout << "\t";  // Print a tab between nodes
            }
        }
        std::cout << std::endl;  // Print a newline after each level
    }

    std::cout << std::endl;

    // Second representation: triangular form
    for (size_t i = 0; i < _tree.size(); ++i) {  // Loop through each level of the tree
        // Calculate padding to center the current level
        int padding = (_depth - i) * 3 + 3;

        // Print the necessary padding to center the current level
        for (int k = 0; k < padding; ++k) {
            std::cout << " ";
        }

        // Print each node in the current level
        for (size_t j = 0; j < _tree[i].size(); ++j) {
            long valueLength = 0;
            if (static_cast<int>(_tree[i][j]) == _tree[i][j]) {  // Check if the value is an integer
                valueLength = std::to_string(static_cast<int>(_tree[i][j])).length();  // Get the length of the integer value
            }
            else {  // If the value is a floating-point number
                valueLength = std::to_string(static_cast<int>(_tree[i][j] * 100)).length() + 1;  // Get the length of the floating-point value
            }

            // Adjust spacing based on the length of the value
            if (valueLength <= 2) {
                std::cout << "  " << _tree[i][j] << "   ";  // Adjust for short values
            }
            else if (valueLength == 3) {
                std::cout << " " << _tree[i][j] << "  ";  // Adjust for medium-length values
            }
            else {
                std::cout << _tree[i][j] << "  ";  // Adjust for long values
            }
        }
        std::cout << std::endl;  // Print a newline after each level

        // Print connectors between levels
        if (i < _tree.size() - 1) {  // If not the last level
            // Print the necessary padding for the connectors
            for (int k = 0; k < padding; ++k) {
                std::cout << " ";
            }

            // Print connectors between nodes at the current level
            for (size_t j = 0; j < _tree[i].size(); ++j) {
                std::cout << "/   \\ ";  // Print the connector
            }
            std::cout << std::endl;  // Print a newline after connectors
        }
    }
    std::cout << std::endl;  // Print an extra newline at the end for clarity
}

// Explicit template instantiations for specific types
template class BinaryTree<bool>;  // Instantiate BinaryTree for bool type
template class BinaryTree<double>;  // Instantiate BinaryTree for double type
template class BinaryTree<int>;  // Instantiate BinaryTree for int type
