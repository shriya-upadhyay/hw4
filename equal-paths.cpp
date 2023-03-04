#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
//helper function prototype
int helper(Node * root, bool& comp);

bool equalPaths(Node * root)
{    
	//base case -> return true if tree is empty
	if (root == NULL) {
      return true;
  }
	//create comparison variable
	bool comparison = true;
	//call helper function, passing in comparison operator by reference
	helper(root, comparison);
	//return value of comparison after helper function is called
	return comparison;
}


int helper(Node * root, bool& comp) {
	//base case -> return 0 if node is null (ie we have gone off end of tree)
	if (root == NULL) {
		return 0;
	}
	//case to check if we are on last node in tree -> return 0
	if (root -> left == NULL && root -> right == NULL) {
		return 0;
	}
	//case to check if current node doesn't have left child, if so only recurse on right child
	if(root -> left == NULL) {
		return 1 + helper(root -> right, comp);
	}
	//case to check if current node doesn't have right child, if so only recurse on left child
	else if (root -> right == NULL) {
		return 1 + helper(root -> left, comp);
	}

	//last case takes care of root node and any other typical node in the middle of the tree
	else {
	//recurse on left and right child of the node
	int left_depth = 1 + helper(root -> left, comp);
	int right_depth = 1 + helper(root -> right, comp);
	//if a depth imbalance is found, change value of comp
	if (left_depth != right_depth) {
	comp = false;}
	//return either depth because the function requires integer return
	return left_depth;
	}
}

