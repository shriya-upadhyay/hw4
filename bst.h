#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
		static Node<Key, Value>* successor(Node<Key, Value>* current); // TODO

    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
	int isBalancedhelper(Node<Key, Value>* curr, bool& comp) const; 
	void clearHelper(Node<Key, Value>* curr);


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator()
{
   current_ = getSmallestNode(); 

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    return (current_ == rhs.current_ );
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
     return (current_ != rhs.current_ );

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
		current_ = successor(current_);
		return *this;

}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    clear();

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
	//it tree is empty, assign new Node to root of tree
    if(root_ == NULL) {
			root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
			
		}

    else {
			//traverse through list to find place to insert node
      Node<Key, Value>* curr = root_;
      while(curr != NULL ) {
				//if key is in tree, overwrite current value with updated value
				if (keyValuePair.first == curr -> getKey()) {
					curr -> setValue(keyValuePair.second);
					return;
        }
				//if key < key of current node in traversal, either create new node with key and set it to the current node's left child 
				//or continue traversing
        else if (keyValuePair.first < curr -> getKey()) {
					if (curr -> getLeft() == NULL) {
						Node<Key, Value>* temp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, curr);
						curr -> setLeft(temp);
						return;
          }
          else {
						curr = curr -> getLeft(); 
          }
        }
				//if key > key of current node in traversal, either create new node with key and set it to the current node's right child 
				//or continue traversing
        else if (keyValuePair.first > curr -> getKey())
				{
					if (curr -> getRight() == NULL) {
						Node<Key, Value>* temp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, curr);
            curr -> setRight(temp);
						return;
          }
					else {
						curr = curr -> getRight(); }
        }
      }
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
		//find Node that possesses key value
		Node<Key, Value>* curr = internalFind(key);
		//returns if key value isn't in tree
		if(curr == NULL) {
			return;
		}

		//swap with predecessor if node has two children
		if (curr -> getLeft() != NULL && curr ->getRight() != NULL) {
			nodeSwap(curr, predecessor(curr));
		}
		//if Node has no children, delete it and change its parent's pointers appropriately
		if (curr -> getLeft() == NULL && curr -> getRight() == NULL) {
			//check if node is root
			if(curr == root_) {
				delete curr;
				root_ = NULL;
				return;
			}
			//delete and change if Node is a left child
			if(curr == curr -> getParent() -> getLeft()) {
				(curr -> getParent()) -> setLeft(NULL);
				delete curr;
				return;
			}
			//delete and change if Node is a right child
			else if(curr == curr -> getParent() -> getRight()) {
				curr -> getParent() -> setRight(NULL);
				delete curr;
				return;
			}
		}

		//promote child Node to Node if it only has one child
		else if ((curr -> getLeft() == NULL && curr -> getRight() != NULL) || (curr -> getLeft() != NULL && curr -> getRight() == NULL)) {
			 //check if node has a left child
			 if (curr -> getLeft() != NULL) {
				 //check if current node is the root and update
				 //left child's parent point to NULL
				 //update root to point at current nodes' left child
				 if(curr == root_) {
					 curr -> getLeft() -> setParent(NULL);
					 root_ = curr -> getLeft();
				 }
				 //check if current is a left child
				 //if so update the current node's parent pointer's left child to the curren't nodes left child
				 //update the current node's left child's parent pointer to point at the parent of the current node
				else if (curr == curr -> getParent() -> getLeft()) {
					curr -> getParent() -> setLeft(curr -> getLeft());
					curr -> getLeft() -> setParent(curr -> getParent());
				}
				//check if current is a right child
				//if so update the current node's parent pointer's right pointer to point at current node's left child
				//update the current node's left child's parent pointer to point at the current node's parent
				else {
					(curr -> getParent()) -> setRight(curr -> getLeft());
					curr -> getLeft() ->setParent(curr -> getParent());
				} 
			}
			//check if node has a right child
			else if (curr -> getRight() != NULL) {
				//check if current node is the root and update
				 //right child's parent point to NULL
				 //update root to point at current nodes' right child
				if(curr == root_) {
					 curr -> getRight() -> setParent(NULL);
					 root_ = curr -> getRight();
				 }
				 //check if current is a right child
				 //if so update the current node's parent pointer's right child to the current node's right child
				 //update the current node's right child's parent pointer to point at the parent of the current node
				else if (curr == curr -> getParent() -> getRight()) {
					curr -> getParent() -> setRight(curr -> getRight());
					curr -> getRight() -> setParent(curr -> getParent());
				}
				//check if current is a left child
				//if so update the current node's parent pointer's left pointer to point at current node's right child
				//update the current node's right child's parent pointer to point at the current node's parent
				else {
					curr -> getParent() -> setLeft(curr -> getRight());
					curr -> getRight() -> setParent(curr -> getParent());
				}
			}
			//delete current node pointer 
			delete curr;
			return;
		}

		

}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
	 //return right-most node of left subtree if left child exists
    if (current -> getLeft() != NULL) {
			current = current -> getLeft();
			while (current -> getRight() != NULL) {
				current = current -> getRight();
			}
			return current;
		}

		//otherwise walk up ancestor chain to return first right child pointer's parent
		else {
			while(current == (current -> getParent()) -> getLeft()) {
				current = current -> getParent();
			}
			if(current -> getParent() == NULL) {
				return NULL;
			}
			else {
				return current -> getParent();
			}
		}
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
		 //return left-most node of right subtree if right child exists
    if (current -> getRight() != NULL) {
			current = current -> getRight();
			while (current -> getLeft() != NULL) {
				current = current -> getLeft();
			}
			return current;
		}
		//otherwise walk up ancestor chain to return first left child pointer's parent
		else {
			if(current -> getParent() == NULL) {
				return NULL;
			}
			while(current == (current -> getParent()) -> getRight()) {
				current = current -> getParent();
				if(current -> getParent() == NULL) {
				return NULL;
				}
			}
			return current -> getParent();
		}
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	//return if root = NULL
	if (root_ == NULL) {
		return; }
	
	//call helper
	clearHelper(root_);

  //set root to NULL after done clearing
	root_ = NULL;

}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* curr) {
	//return if current value is NULL (ie we have gone off end of tree)
	if (curr == NULL) {
		return;
	}
	else { 
		//call curr on left subtree
		clearHelper(curr -> getLeft());
		//call curr on right subtree
		clearHelper(curr -> getRight());
		//delete curr
		delete curr;
	}
	
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
	//set curr value to root_
    Node<Key, Value>* curr = root_;
		//return NULL if tree is empty
		if (curr == NULL) {
			return NULL;
		}

		//else traverse through tree left subtree to find smallest key
		Node<Key, Value>* minKey = curr;
		while(curr != NULL) {
			if (curr -> getKey() < minKey -> getKey()) {
				minKey = curr;
			}
			curr = curr -> getLeft();
		}

	//return the minimum key
	return minKey;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
		//set curr = to root
    Node<Key, Value>* curr = this -> root_;
		if(curr == NULL) {
			return NULL;
		}
		//traverse tree to find node, going left if key < current node's key
		//and right if key > current node's key 
		while(curr != NULL){
		//return node when found
		if (curr -> getKey() == key) {
			return curr;
		}
		else if (key < curr -> getKey()) {
			curr = curr -> getLeft();
		}
		else if (key > curr -> getKey()) {
			curr = curr -> getRight();
		}
	}
	//if node is never found, return null
	return NULL;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
	//if tree is empty, returns true 
  if (root_ == NULL) {
      return true;
  }
	
	bool comparison = true;
	//calculates height of left subtree and right subtree adding one to account for root
	int left_height = 1 + isBalancedhelper(root_ -> getLeft(), comparison);
	int right_height = 1 + isBalancedhelper(root_ -> getRight(), comparison);

	if (!comparison) {
		return false;
	}

	//account for subtrees of root node
	else if ((left_height - right_height) > 1) {
		return false;
	}

	else if ((left_height - right_height) < -1) {
		return false;
	}

	else {
		return true;
	}


}


//helper function to account for balance of subtrees
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::isBalancedhelper(Node<Key, Value>* root, bool &comp) const {
	//if we hit base case, function will return 0 for height
	if (root == NULL) {
		return 0;
	}

	//if Node is a leaf node, return 1
	if (root -> getLeft() == NULL && root -> getRight() == NULL) {
		return 1;
	}

	//if Node only has one child, check if the height of its other subtree is greater than 1, since it must be <=1
	//for the bst property to be satisfied 
	//otherwise, set comp variable to false

	else if (root -> getLeft() == NULL) {
		if ( 1 + isBalancedhelper( root -> getRight(), comp) > 1) {
			comp = false;
		}

		return 1 + isBalancedhelper( root -> getRight(), comp);
	}

	else if (root -> getRight() == NULL ) {
		if ( 1 + isBalancedhelper( root -> getLeft(), comp) > 1) {
			comp = false;
		}
		return 1 + isBalancedhelper( root -> getLeft(), comp);
	}

	//account for case in which Node has two children 
	//calculate height of both of its subtrees
	else 	{
		int left_height = 1+ isBalancedhelper( root -> getLeft(), comp);
		int right_height = 1 + isBalancedhelper( root -> getRight(), comp);
		//if height of tree is imbalanced and comp is currently true, set comp to false
		if( left_height - right_height > 1 || left_height - right_height < -1) {
			if (comp) {
				comp = false;
			}
		}
		// return whichever has greater height, left subtree or right subtree since the height has to be maximized
		if (left_height > right_height) {
			return left_height;
		}
		else {
			return right_height;
		}
	}
	
}




template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
