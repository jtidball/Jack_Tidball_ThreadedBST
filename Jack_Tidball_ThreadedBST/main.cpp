



#include <iostream>
#include <string>
#include "BST.h"
using namespace std;

int main() {

	cout << "Jack Tidball CSIS 215 - Double Threaded Binary Search Tree\n";

	BST<int, std::string>* keyPairs = new BST<int, std::string>();

	keyPairs->insert(77, "seventy-seven");
	keyPairs->insert(70, "seventy");
	keyPairs->insert(75, "seventy-five");
	keyPairs->insert(66, "sixty-six");
	keyPairs->insert(79, "seventy-nine");
	keyPairs->insert(68, "sixty-eight");
	keyPairs->insert(67, "sixty-seven");
	keyPairs->insert(69, "sixty-nine");
	keyPairs->insert(90, "ninety");
	keyPairs->insert(85, "eighty-five");
	keyPairs->insert(83, "eighty-three");
	keyPairs->insert(87, "eighty-seven");
	keyPairs->insert(65, "sixty-five");
	



};