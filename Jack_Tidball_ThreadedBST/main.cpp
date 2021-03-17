



#include <iostream>
#include <string>
#include "BST.h"


using namespace std;

int main() {

	cout << "\n\nJack Tidball CSIS 215 - Double Threaded Binary Search Tree\n\n";

	
	int arr[] = { 77, 70, 75, 66, 79, 68, 67, 69, 90, 85, 83, 87, 65};
	std::string arr1[] = { "seventy-seven", "seventy", "seventy-five", "sixty-six", "seventy-nine",
	"sixty-eight", "sixty-seven", "sixty-nine", "ninety", "eighty-five", "eighty-three", "eighty-seven", "sixty-five" };
	

	BST<int, std::string>* keyPairs = new BST<int, std::string>();
	int n = sizeof(arr) / sizeof(arr[0]);
	int m = sizeof(arr1) / sizeof(arr1[0]);

	if (m != n) {
		cout << "Lists are different Sizes";
		return 0;
	}
	
	for (int i = 0; i < n; i++) {
		keyPairs->insert(arr[i], arr1[i]);
	}

	cout << "The size of the Tree is: " << keyPairs->size() << endl;
	
	cout << "Inorder Print: \n";
	keyPairs->inorderPrint();

	cout << "\n\n\nPrint Reverse: \n";
	keyPairs->reverseInorderPrint();

	cout << "\n\n\nWhen Printed the tree looks like: \n";
	keyPairs->print();

	cout << "\nTry to find 70: ";
	cout << (keyPairs->find(70));

	
	return 1;
};