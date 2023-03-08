#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
    virtual void insert_fix (AVLNode<Key, Value>* p, AVLNode<Key, Value>* n); // TODO
    virtual void rotateRight(AVLNode<Key, Value>* node);
    virtual void rotateLeft(AVLNode<Key, Value>* node);
    virtual int ZZcheck(AVLNode<Key, Value>* g, AVLNode<Key, Value>* n);
    void removeFix(AVLNode<Key,Value>* n, int diff);
		virtual int getHeight(AVLNode<Key,Value>* n);



};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    if(BinarySearchTree<Key, Value>::empty()) {
			this -> root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
			AVLNode<Key, Value>* c = static_cast<AVLNode<Key, Value>*>(this -> root_);
			c -> setBalance(0);
			return;
		}
    else {
		AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*> (this -> root_);
		AVLNode<Key, Value>* curr_child = static_cast<AVLNode<Key, Value>*> (this -> root_);
		while(curr != NULL ) {
			if (new_item.first == curr -> getKey()) {
				curr -> setValue(new_item.second);
				return;
			}

			else if (new_item.first < curr -> getKey()) {
				if (curr -> getLeft() == NULL) {
					AVLNode<Key, Value>* temp = new AVLNode<Key, Value>(new_item.first, new_item.second, curr);
					curr -> setLeft(temp);
					curr_child = curr -> getLeft();
					curr_child -> setBalance(0);
					break;
				}
				else {
					curr = curr -> getLeft(); 
				}
			}

			else if (new_item.first > curr -> getKey()) {
				if(curr -> getRight() == NULL ) {
					AVLNode<Key, Value>* temp = new AVLNode<Key, Value>(new_item.first, new_item.second, curr);
					curr -> setRight(temp);
					curr_child = curr -> getRight();
					curr_child -> setBalance(0);
					break;
				}
				else {
					curr = curr -> getRight();
				}

			}
		}

		/*if ( curr -> getParent() && curr -> getParent() -> getParent() && curr -> getParent() -> getParent() -> getLeft()) {
		std:: cout << int(curr -> getParent() -> getParent() -> getLeft() -> getBalance()) << std::endl;}*/
    if (curr -> getBalance() == -1 ) {
        curr -> setBalance(0);
    }
    else if (curr -> getBalance() == 1 ) {
        curr -> setBalance(0);
    }
    else if (curr -> getBalance() == 0) {
        if (curr_child == curr_child -> getParent() -> getLeft()) {
            curr_child -> getParent() -> updateBalance(-1);
        }
        else if (curr_child == curr_child ->getParent() -> getRight()) {
            curr -> updateBalance(1);
        }
        insert_fix(curr, curr_child);
    }
    }

	BinarySearchTree<Key, Value>::printRoot(this -> root_);
    
}

template<class Key, class Value>
void AVLTree<Key, Value>:: insert_fix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n) {
if (p == NULL || p -> getParent() == NULL) {
    return;
}
AVLNode<Key,Value>* g = p -> getParent();
if (p == p -> getParent() -> getLeft()) {
    g -> updateBalance(-1);
    if (g -> getBalance() == 0) {
        return;
    }
    if (g -> getBalance() == -1 ) {
        insert_fix(g, p);
    }

    if (g -> getBalance() == -2) {
        if (ZZcheck(g, n) == 1) {
        rotateRight(g);
        p -> setBalance(0);
        g -> setBalance(0);
        }
        else {
            rotateLeft(p);
            rotateRight(g);
						if (n -> getBalance() == -1 ) {
							p -> setBalance(0);
							g -> setBalance(1);
							n -> setBalance(0);
						}

						else if ( n -> getBalance() == 0 ) {
							p -> setBalance(0);
							g -> setBalance(0);
							n -> setBalance(0);
						}

						else if ( n -> getBalance() == 1 ) {
							p -> setBalance(-1);
							g -> setBalance(0);
							n -> setBalance(0);
						}
        }
    }
}
else if (p == p -> getParent() -> getRight()) {
    g -> updateBalance(1);
    if (g -> getBalance() == 0) {
        return;
    }
    if (g -> getBalance() == 1 ) {
        insert_fix(g, p);
    }

    if (g -> getBalance() == 2 ) {
        if (ZZcheck(g, n) == 1) {
            rotateLeft(g);
            p -> setBalance(0);
            g -> setBalance(0);
        }
        else {
            rotateRight(p);
            rotateLeft(g);
						if (n -> getBalance() == 1 ) {
							p -> setBalance(0);
							g -> setBalance(-1);
							n -> setBalance(0);
						}
						else if (n -> getBalance() == 0 ) {
							p -> setBalance(0);
							g -> setBalance(0);
							n -> setBalance(0);
						}
						else if (n -> getBalance() == -1 ) {
							p -> setBalance(1);
							g -> setBalance(0);
							n -> setBalance(0);
						}
        }
    }
	}

}

template<class Key, class Value>

int AVLTree<Key, Value> :: ZZcheck(AVLNode<Key, Value>* g, AVLNode<Key, Value>* n) {
   //return 1 for zig-zig
		if ( g -> getRight() != NULL && g-> getRight() -> getRight() != NULL) {
    if ( n == g -> getRight() -> getRight() ) {
        return 1;
    }
		}
    //return 1 for zig-zig
		if ( g -> getLeft() != NULL && g-> getLeft() -> getLeft() != NULL) {
    if (n == g -> getLeft() -> getLeft()) {
        return 1;
    }
		}
    //return 0 for zig-zag
    return 0;
    
}

template<class Key, class Value>
void AVLTree<Key, Value> :: rotateRight(AVLNode<Key, Value>* node) {
		AVLNode<Key,Value>* prev_node_child = NULL;
		AVLNode<Key, Value>* prev_node_parent = NULL;
		AVLNode<Key, Value>* new_node_child = NULL; 

		if (node -> getLeft()) {
     prev_node_child = node -> getLeft(); }
		if (node -> getParent()) {
     prev_node_parent = node -> getParent(); 
		}
		if (prev_node_child && prev_node_child -> getRight()) {
    new_node_child = prev_node_child -> getRight(); 
		}

		if(prev_node_child) {
    prev_node_child -> setRight(node); }
    node -> setParent(prev_node_child);


		if (new_node_child ) {
    new_node_child -> setParent(node);}
		node -> setLeft(new_node_child);

		if (prev_node_child){
    prev_node_child -> setParent(prev_node_parent); }

		if (prev_node_parent) {
			if ( prev_node_parent -> getRight() == node) {
			prev_node_parent -> setRight(prev_node_child); 
			}
			else {
				prev_node_parent -> setLeft(prev_node_child); 
			}		
		}

		if(node == this -> root_) {
			this -> root_ = prev_node_child;
		}

}

template<class Key, class Value>
void AVLTree<Key, Value> :: rotateLeft(AVLNode<Key, Value>* node) {
    AVLNode<Key,Value>* prev_node_child = NULL;
		AVLNode<Key, Value>* prev_node_parent = NULL;
		AVLNode<Key, Value>* new_node_child = NULL; 



		if (node -> getRight()) {
		 prev_node_child = node -> getRight();
		}

		if(node -> getParent()) {
     prev_node_parent = node -> getParent();
		}

		if (prev_node_child && prev_node_child -> getLeft()) {
     new_node_child = prev_node_child -> getLeft();
		}

		if (prev_node_child) {
    prev_node_child -> setLeft(node); }
    node -> setParent(prev_node_child);

		
		if(new_node_child) {
    new_node_child -> setParent(node); }

		node -> setRight(new_node_child);


		if(prev_node_child) {
    prev_node_child -> setParent(prev_node_parent); 
		}

		if (prev_node_parent) {
			if ( prev_node_parent -> getRight() == node) {
			prev_node_parent -> setRight(prev_node_child); 
			}
			else {
				prev_node_parent -> setLeft(prev_node_child); 
			}
		}

		if(node == this -> root_) {
			this -> root_ = prev_node_child;
		}
}


/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{

	if(this -> root_ == NULL) {
		return;
	}
  AVLNode<Key, Value>* n = static_cast<AVLNode<Key, Value>*> (BinarySearchTree<Key, Value>::internalFind(key));
	if (n == NULL) {
		return;
	}
		
  if (n -> getRight() != NULL && n -> getLeft() != NULL) {
    nodeSwap(n, static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::predecessor(n)));
  }

	if(n == this -> root_) {
		delete n;
		this -> root_ = NULL;
		return;
	}

    AVLNode<Key, Value>* p = n -> getParent();
    int diff = 0;
    if (p != NULL ) {
        if (n == p -> getLeft()) {
            diff = 1;
        }
        if (n == p -> getRight()) {
            diff = -1;
        }
    }

    if (n -> getLeft() == NULL && n -> getRight() == NULL) { 
			if(n == n -> getParent() -> getLeft()) {
				(n -> getParent()) -> setLeft(NULL);
				delete n;
			}
			//delete and change if Node is a right child
			else if(n == n -> getParent() -> getRight()) {
				n -> getParent() -> setRight(NULL);
				delete n;
			}
		}


    removeFix(p, diff);

	BinarySearchTree<Key, Value>::printRoot(this -> root_);


}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* n, int diff) {
    if (n == NULL) {
        return;
    }

		int ndiff = 0;
		AVLNode<Key,Value>* p = n -> getParent();

		if (n != this -> root_ && p != this -> root_) {
			if (p == p -> getParent() -> getLeft()) {
				ndiff = 1; 
			}

			if (p == p -> getParent() -> getRight()) {
				ndiff = -1;
			}
		}

		if (diff == -1 ) {
			if (n -> getBalance() + diff == -2) {
				AVLNode<Key,Value>* c;
				if (getHeight(n -> getLeft()) > getHeight( n -> getRight())) {
				 	c = n -> getLeft(); }
				else {
					 c = n -> getRight();
				}
				if (c -> getBalance() == -1 ) {
					rotateRight(n);
					c -> setBalance(0);
					n -> setBalance(0);
					removeFix(p, ndiff);
				}

				else if (c -> getBalance() == 0) {
					rotateRight(n);
					n -> setBalance(-1);
					c -> setBalance(1);
					return;
				}

				else if (c -> getBalance() == 1){
					AVLNode<Key,Value>* g = c -> getRight();
					int g_balance = g -> getBalance();
					rotateLeft(c);
					rotateRight(n);
					if (g_balance == 1) {
						n -> setBalance(0);
						c -> setBalance(-1);
						g -> setBalance(0);
					}
					else if (g_balance == 0) {
						n -> setBalance(0);
						c -> setBalance(0);
						g -> setBalance(0);
					}
					else if (g_balance == -1) {
						n -> setBalance(1);
						c -> setBalance(0);
						g -> setBalance(0);
					}
					removeFix(p, ndiff);
				}
			}
			else if (n -> getBalance() + diff == -1) {
				n -> setBalance(-1);
				return;
			}

			else if (n -> getBalance() + diff == 0) {
				n -> setBalance(0);
			}
		}

		else if (diff == 1) {
			if (n -> getBalance() + diff == 2) {
				AVLNode<Key,Value>* c;
				if (getHeight(n -> getLeft()) > getHeight( n -> getRight())) {
				 	c = n -> getLeft(); }
				else {
					 c = n -> getRight();
				}
				if (c -> getBalance() == 1 ) {
					rotateLeft(n);
					c -> setBalance(0);
					n -> setBalance(0);
					removeFix(p, ndiff);
				}

				else if (c -> getBalance() == 0) {
					rotateLeft(n);
					n -> setBalance(1);
					c -> setBalance(-1);
					return;
				}

				else if (c -> getBalance() == -1){
					AVLNode<Key,Value>* g = c -> getLeft();
					int g_balance = g -> getBalance();
					rotateRight(c);
					rotateLeft(n);
					if (g_balance == -1) {
						n -> setBalance(0);
						c -> setBalance(1);
						g -> setBalance(0);
					}
					else if (g_balance == 0) {
						n -> setBalance(0);
						c -> setBalance(0);
						g -> setBalance(0);
					}
					else if (g_balance == 1) {
						n -> setBalance(-1);
						c -> setBalance(0);
						g -> setBalance(0);
					}
					removeFix(p, ndiff);
				}
			}
			else if (n -> getBalance() + diff == 1) {
				n -> setBalance(1);
				return;
			}

			else if (n -> getBalance() + diff == 0) {
				n -> setBalance(0);
			}

		}
    
}
template<class Key, class Value>
int AVLTree<Key, Value>:: getHeight(AVLNode<Key,Value>* n) {
	if (n == NULL) {
		return 0;
	}
	if (getHeight(n -> getLeft()) > getHeight( n -> getRight())) {
		return 1 + getHeight(n -> getLeft());
	}
	else {
		return 1 + getHeight( n -> getRight());
		 }

}


template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
