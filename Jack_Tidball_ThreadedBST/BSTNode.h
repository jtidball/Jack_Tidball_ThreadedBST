// template implementation

#include "book.h"
#include "BinNode.h"

#ifndef BSTNODE_H
#define BSTNODE_H

// Simple binary tree node implementation
template <typename Key, typename E>
class BSTNode : public BinNode<E> {
private:
	Key k;                  // The node's key
	E it;                   // The node's value
	BSTNode* lc;            // Pointer to left child
	BSTNode* rc;            // Pointer to right child
	bool threadPointerLeft : 1; 
    bool threadPointerRight : 1; // true = tread, 1    false = pointer, 0

public:
	// Two constructors -- with and without initial values
	BSTNode() {
		lc = rc = NULL; 
	}

	BSTNode(Key K, E e, BSTNode* l = NULL, BSTNode* r = NULL)
	{
		k = K;
		it = e; 
		lc = l; 
		rc = r; 

		threadPointerLeft = true;
		threadPointerRight = true;
	}

	~BSTNode() {}            


	void setLeftThreadPointer(bool TP) { threadPointerLeft = TP; }

	void setRightThreadPointer(bool TP) { threadPointerRight = TP; }

	bool getLeftThreadPointer() const { return threadPointerLeft; }

	bool getRightThreadPointer() const { return threadPointerRight; }

	// Functions to set and return the value and key
	E& element() { return it; }
	void setElement(const E& e) { it = e; }
	Key& key() { return k; }
	void setKey(const Key& K) { k = K; }

	// Functions to set and return the children
	inline BSTNode* left() const { return lc; }

	inline BSTNode* right() const { return rc; }

	void setLeft(BinNode<E>* b, bool tp) {
		lc = (BSTNode*)b;
		if (tp == true) {
			threadPointerLeft = true;
		} else {
			threadPointerLeft = false;
		}
	}
	

	void setRight(BinNode<E>* b, bool tp) {
		rc = (BSTNode*)b; // set the right child pointer to the passed in node 
		if (tp == true) {
			threadPointerRight = true; // set the bit wise 
		} else {
			threadPointerRight = false;
		}
	}

	
	    // Return true if it is a leaf, false otherwise
    bool isLeaf() {
        if ((getLeftThreadPointer()) && (getRightThreadPointer())) {
            return true;
		}
		else {
			return false;
		} 
    }
};

#endif

