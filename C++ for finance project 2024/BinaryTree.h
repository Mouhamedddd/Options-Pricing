#pragma once
#include  <vector>

//BinaryTree is a template classs 
template<typename T>
class BinaryTree {

private:
	int _depth;//member _depth for to represent N
	std::vector<std::vector<T>> _tree;//_tree is a vector of vector to hold data (of type T)

public:
	//Ourr constructors


	BinaryTree(int depth);

	BinaryTree() : _depth(0) {

	}

	//Destructor:
	~BinaryTree();

	int getDepth();
	//We have to implemnt some methods : setDepth(int) // setNode(i,j,T)//getNode(int i, int j) //display() --> check cpp file for implemntation
	void setDepth(int depth);// setter for depth that resizes _treeand allocate / deallocate porperly the vector in the tree
	void setNode(int i, int j, T value_node);// sets a value in our tree at the position (i,j)
	T getNode(int i, int j) const;//which retrives the corresponding value
	void display();//print all the value stored (the output we want is described in the figure 2 of project description)


};
