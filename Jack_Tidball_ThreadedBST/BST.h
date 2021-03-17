

// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// This file includes all of the pieces of the BST implementation

// Include the node implementation
#include "BSTNode.h"

// Include the dictionary ADT
#include "dictionary.h"

#ifndef BST_H
#define BST_H

using namespace std;

// Binary Search Tree implementation for the Dictionary ADT
template <typename Key, typename E>
class BST : public Dictionary<Key, E> {
private:
    BSTNode<Key, E>* root;   // Root of the BST

    int nodecount;         // Number of nodes in the BST

    // Private "helper" functions
    void clearhelp(BSTNode<Key, E>*);
    BSTNode<Key, E>* inserthelp(BSTNode<Key, E>*, const Key&, const E&);
    BSTNode<Key, E>* deletemin(BSTNode<Key, E>*);
    BSTNode<Key, E>* getmin(BSTNode<Key, E>*);
    BSTNode<Key, E>* removehelp(BSTNode<Key, E>*, const Key&);
    std::string findhelp(BSTNode<Key, E>*, const Key&) const;
    void printhelp(BSTNode<Key, E>*, int) const;
    void vist(BSTNode<Key, E>*) const;

    
public:
	BST() { root = NULL; nodecount = 0; }  // Constructor

	//Note from Prof Sipantzi -- I've commented out the destructor
	//since you would have to change clearhelp() to make it work with
	//doubly-threaded trees and that is not part of the assignment.
	//~BST() { clearhelp(root); }            // Destructor

	void clear()   // Reinitialize tree
	{
		clearhelp(root); root = NULL; nodecount = 0;
	}

	// Insert a record into the tree.
	// k Key value of the record.
	// e The record to insert.
	void insert(const Key& k, const E& e) {
		root = inserthelp(root, k, e);
		nodecount++;
	}

	// Return Record with key value k, NULL if none exist.
	// k: The key value to find. */
	// Return some record matching "k".
	// Return true if such exists, false otherwise. If
	// multiple records match "k", return an arbitrary one.
	std::string find(const Key& k) const {
		return findhelp(root, k);
	}

	// Return the number of records in the dictionary.
	int size() {
		return nodecount; 
	}

	void print() const { // Print the contents of the BST
		if (root == NULL) cout << "The BST is empty.\n";
		else printhelp(root, 0);
	}

	// INORDER PRINT -- WORKS
	void inorderPrint() {
		BSTNode<Key, E>* curr = root; // create a temp BST object 
		if (curr == NULL) {		// check to see if there are values inserted in the tree
			cout << "We must insert first";
		} else {
			while (curr->left() != NULL) { //  go to the left most element 
				curr = curr->left();
			}
			while (curr->right() != NULL) { // incrementally we move over one at a time 
				cout << "\n" << curr->element(); // first print out left most item 
				//Successor threads implemented and demonstrated
				if ((curr->getRightThreadPointer()) == true) { // if the curr right pointer is a thread 
					curr = curr->right(); // follow the thread and reiterate
				} else { // otherwise we will still move right but we will check for children
					curr = curr->right(); // move one over to the right but then follow left until reach thread
					while ((curr->getLeftThreadPointer()) == false) { 
						curr = curr->left(); // print left most on the branch then follow thread
					}
				}
			}
			cout << "\n" << curr->element(); // print the last element 
		}
	}

	// REVERSE PRINT -- WORKS
	void reverseInorderPrint() {
		BSTNode<Key, E>* curr = root;
		if (curr == NULL) { // check to see if there are values inserted in the tree
			cout << "We must insert first";
		}
		while (curr->right() != NULL) { // go as far right possible 
			curr = curr->right();
		}
		while (curr->left() != NULL) { // we move the opposite way now we move left incrementally
			cout << "\n" << curr->element(); // print the first right element and set the next before we iterate again
			if ((curr->getLeftThreadPointer()) == true) { // if the pointer is a thread 
				curr = curr->left(); //  go left once more and reiterate
			} else {
				curr = curr->left();  // set curr to the left 
				while ((curr->getRightThreadPointer())== false) { // go to the right most node on the branch 
					curr = curr->right();
				}
			}
		}
		cout << "\n" << curr->element(); // print the last element 
	}

	
};

// Visit -- prints out root
template <typename Key, typename E>
void BST<Key, E>::vist(BSTNode<Key, E>* r) const {
	cout << "Node - " << r->element() << endl;
}

// Clean up BST by releasing space back free store
template <typename Key, typename E>
void BST<Key, E>::clearhelp(BSTNode<Key, E>* root) {
	if (root == NULL) return;
	clearhelp(root->left());
	clearhelp(root->right());
	delete root;
}


// Insert a node into the BST, returning the updated tree
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::inserthelp(BSTNode<Key, E>* root, const Key& k, const E& it) {
	if (root == NULL) {									// Check to see if the tree has values inserted
		return new BSTNode<Key, E>(k, it, NULL, NULL);	// if so we need to create the first node
	}
	// check to see which side of the tree to place it on 
	if (k < root->key()) {
		if ((root->getLeftThreadPointer()) == true) { // if left pointer is a thread 
			BSTNode<Key, E>* node = new BSTNode<Key, E>(k, it, NULL, NULL); // create new node 
			node->setRight(root, true); // right child pointer is going to equal the root, both the left and right are going to be threads
			node->setLeft(root->left(), true); //set the left side pointer to the point to the root left child
			root->setLeft(node, false); // then we can set the node as a left child of the root 
		} else {
			root->setLeft(inserthelp(root->left(), k, it), false); // recursively go left and check again 
		}
	} else { 
		if ((root->getRightThreadPointer()) == true) { // if right pointer is a thread 
			BSTNode<Key, E>* node = new BSTNode<Key, E>(k, it, NULL, NULL); // create a new node 
			node->setRight(root->right(), true); // same exact thing as above but now we are going to the right because the key was larger 
			node->setLeft(root, true);
			root->setRight(node, false); // insert the node to the right 
		} else { 
			root->setRight(inserthelp(root->right(), k, it), false); // otherwise go right and check again
		}
	}
	return root; // return the tree
}

// Delete the minimum value from the BST, returning the revised BST
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
getmin(BSTNode<Key, E>* rt) {
	if (rt->left() == NULL)
		return rt;
	else return getmin(rt->left());
}


// Find a node with the given key value
template <typename Key, typename E>
std::string BST<Key, E>::findhelp(BSTNode<Key, E>* root, const Key& k) const {
	if (root == NULL) return NULL;          
	if (k < root->key())
		return findhelp(root->left(), k);   
	else if (k > root->key())
		return findhelp(root->right(), k); 
	else {
		//E* temp = new E;
		//*temp = root->element();
		return root->element();  
	}
}


template <typename Key, typename E>
void BST<Key, E>::printhelp(BSTNode<Key, E>* root, int level) const { // Same Print function as given just only want to print when threadpointer is false, ie: a pointer
	if (root == NULL) { // check to see if there are values inserted in the tree
		return;
	}
	// when we rotate the tree clockwise right is on the top 
	if ((root->getRightThreadPointer()) == false) { // check to see if the right is a thread or pointer 
		printhelp(root->right(), level + 1); // if so recursively print right 
	}
	for (int i = 0; i < level; i++) { // printing the spaces
		cout << "  ";
	}
	cout << root->key() << "\n"; // print the number
	if ((root->getLeftThreadPointer()) == false) { //check to see if the left is a thread or pointer, if pointer do the left
		printhelp(root->left(), level + 1); // if so recursivly print left subtree 
	}
}

#endif

