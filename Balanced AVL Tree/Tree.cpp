#include "Tree.h"
#include <queue> //for breadth first level count
#include <algorithm> //for max function in calculating node heights

Tree::TreeNode* Tree::helpInsert(TreeNode* root, string value, string name) {
	if (root == nullptr) {
		if (this->values.find(value) != this->values.end()) { //duplicate value
			cout << "unsuccessful\n";
			return root;
		}
		else {
			this->values.insert(value);
			cout << "successful\n";
			return new TreeNode(value, name);
		}
	}
	else if (stoi(value) < stoi(root->UFID)) {
		root->left = helpInsert(root->left, value, name);
		root->heightVal = updateHeight(root);
		root->balanceFactor = updateBalance(root);
		checkBalance(root);
	}
	else if (stoi(value) > stoi(root->UFID)) {
		root->right = helpInsert(root->right, value, name);
		root->heightVal = updateHeight(root);
		root->balanceFactor = updateBalance(root);
		checkBalance(root);
	}
	else { //the ID values are equal (aka value is not unique)
		cout << "unsuccessful\n";
		return root;
	}
	return root;
}

void Tree::insert(string ID, string NAME) {
	this->root = helpInsert(this->root, ID, NAME);
}

void Tree::checkBalance(TreeNode*& root) {
	if (root->balanceFactor < -1) { //right heavy
		if (root->right->balanceFactor >= 1) { //right subtree is left heavy
			root = rightLeftRotation(root, root->right);
		}
		else {
			root = leftRotation(root, root->right);
		}
	}
	else if (root->balanceFactor > 1) { //left heavy
		if (root->left->balanceFactor <= -1) { //left subtree is right heavy
			root = leftRightRotation(root, root->left);
		}
		else {
			root = rightRotation(root, root->left);
		}
	}
}

//updates height of subtree for use in updateBalance to determine balance factor
int Tree::updateHeight(TreeNode*& root) {
	if (root->left != nullptr && root->right != nullptr) {
		return max(root->left->heightVal, root->right->heightVal) + 1;
	}
	else if (root->left == nullptr && root->right != nullptr) {
		return root->right->heightVal + 1;
	}
	else if (root->left != nullptr && root->right == nullptr) {
		return root->left->heightVal + 1;
	}
	else {
		return 0;
	}
}

//determines balance factor of passed in node using its available children
int Tree::updateBalance(TreeNode*& root) {
	if (root->left != nullptr && root->right != nullptr) {
		return (root->left->heightVal + 1) - (root->right->heightVal + 1);
	}
	else if (root->left == nullptr && root->right != nullptr) {
		return -root->right->heightVal - 1;
	}
	else if (root->left != nullptr && root->right == nullptr) {
		return root->left->heightVal + 1;
	}
	else {
		return 0;
	}
}

Tree::TreeNode* Tree::leftRotation(TreeNode* root, TreeNode* child) { //right right case rotation
	root->right = child->left;
	child->left = root;
	//resetting the heights/balance factors of each node involved
	root->heightVal = updateHeight(root);
	root->balanceFactor = updateBalance(root);
	child->heightVal = updateHeight(child);
	child->balanceFactor = updateBalance(child);
	if (child->right != nullptr) {
		child->right->heightVal = updateHeight(child->right);
		child->right->balanceFactor = updateBalance(child->right);
	}
	return child;
}

Tree::TreeNode* Tree::rightRotation(TreeNode* root, TreeNode* child) { //left left case rotation
	root->left = child->right;
	child->right = root;
	//resetting the heights/balance factors of each node involved
	root->heightVal = updateHeight(root);
	root->balanceFactor = updateBalance(root);
	child->heightVal = updateHeight(child);
	child->balanceFactor = updateBalance(child);
	if (child->left != nullptr) {
		child->left->heightVal = updateHeight(child->right);
		child->left->balanceFactor = updateBalance(child->right);
	}
	return child;
}

Tree::TreeNode* Tree::leftRightRotation(TreeNode* root, TreeNode* child) { //left right case rotation
	root->left = leftRotation(child, child->right); //left rotation of child and grandchild
	root = rightRotation(root, root->left); //right rotation of root and new child
	return root;
}

Tree::TreeNode* Tree::rightLeftRotation(TreeNode* root, TreeNode* child) { //right left case rotation
	root->right = rightRotation(child, child->left); //right rotation of child and grandchild
	root = leftRotation(root, root->right); //left rotation of root and new child
	return root;
}

//removes the node with the specified ID if it exists within the tree and reassigns pointers if necessary
bool Tree::helpRemoveID(TreeNode* root, string ID, TreeNode* parent, bool leftChild) {
	if (root == nullptr) {
		return false;
	}
	else if (stoi(ID) == stoi(root->UFID)) { //comparing integer ID values
		reassignPointers(root, parent, leftChild);
		cout << "successful\n";
		return true;
	}
	else if (stoi(ID) < stoi(root->UFID)) {
		parent = root;
		return helpRemoveID(root->left, ID, parent, true);
	}
	else {
		parent = root;
		return helpRemoveID(root->right, ID, parent, false);
	}
}

void Tree::removeID(string ID) {
	bool result = false;
	result = helpRemoveID(this->root, ID, this->root, false);
	if (result == false) {
		cout << "unsuccessful\n";
	}
}

//prints the name value of the associated node with the passed in ID if it exists within the tree
bool Tree::helpSearchID(TreeNode* root, string ID) {
	if (root == nullptr) {
		return false;
	}
	else if (stoi(root->UFID) == stoi(ID)) { //comparing integer values of each ID
		cout << root->name << endl;
		return true;
	}
	else if (stoi(ID) < stoi(root->UFID)) {
		return helpSearchID(root->left, ID);
	}
	else {
		return helpSearchID(root->right, ID);
	}
}

void Tree::searchID(string ID) {
	bool result = false;
	result = helpSearchID(this->root, ID);
	if (result == false) {
		cout << "unsuccessful\n";
	}
}

//code for traversals based on trees lecture slides
void Tree::helpInOrder(TreeNode* root) {
	if (root == nullptr) {
		cout << "";
	}
	else {
		helpInOrder(root->left);
		if (root->left != nullptr) { //printing out commas during/after recursion
			cout << ", ";
		}
		cout << root->name;
		if (root->right != nullptr) {
			cout << ", ";
		}
		helpInOrder(root->right);
	}
}

void Tree::printInOrder() { //left, root, right
	helpInOrder(this->root);
	cout << endl;
}

void Tree::helpPreOrder(TreeNode* root) {
	if (root == nullptr) {
		cout << "";
	}
	else {
		cout << root->name;
		if (root->left != nullptr || root->right != nullptr) { //conditions for printing comma before/after value
			cout << ", ";
		}
		helpPreOrder(root->left);
		if (root->left != nullptr && root->right != nullptr) {
			cout << ", ";
		}
		helpPreOrder(root->right);
	}
}

void Tree::printPreOrder() { //root, left, right
	helpPreOrder(this->root);
	cout << endl;
}

void Tree::helpPostOrder(TreeNode* root) {
	if (root == nullptr) {
		cout << "";
	}
	else {
		helpPostOrder(root->left);
		if (root->left != nullptr && root->right != nullptr) { //conditions for printing comma before/after value
			cout << ", ";
		}
		helpPostOrder(root->right);
		if (root->left != nullptr || root->right != nullptr) {
			cout << ", ";
		}
		cout << root->name;
	}
}

void Tree::printPostOrder() { //left, right, root
	helpPostOrder(this->root);
	cout << endl;
}

void Tree::helpPrintLevels(TreeNode* root) {
	int height = 0;
	int currLevel = 1; //number of nodes in current level
	int nextLevel = 0;
	queue<TreeNode*> q;
	if (root == nullptr) {
		cout << 0;
	}
	else {
		q.push(root);
		while (!q.empty()) {
			nextLevel = 0;
			for (int i = 0; i < currLevel; i++) { //for each node in the current level, push it onto the queue
				if (q.front()->left != nullptr) {
					q.push(q.front()->left);
					nextLevel++;
				}
				if (q.front()->right != nullptr) {
					q.push(q.front()->right);
					nextLevel++;
				}
				q.pop(); //pop the parent of the nodes just added
			}
			height++;
			currLevel = nextLevel;
		}
		cout << height << endl;
	}
}

void Tree::printLevelCount() {
	helpPrintLevels(this->root);
}

//prints the id of the node with the passed in name if it exists within the tree
bool Tree::helpSearchName(TreeNode* root, string name, bool atLeastOne) {
	if (root == nullptr) {
		return atLeastOne;
	}
	else {
		if (root->name == name) {
			cout << root->UFID << endl;
			atLeastOne = true;
		}
		atLeastOne = helpSearchName(root->left, name, atLeastOne);
		atLeastOne = helpSearchName(root->right, name, atLeastOne);
	}
	return atLeastOne;
}

void Tree::searchName(string name) {
	bool result = false;
	name.erase(remove(name.begin(), name.end(), '\"'), name.end());
	result = helpSearchName(this->root, name, false);
	if (result == false) {
		cout << "unsuccessful\n";
	}
}

//removes the nth node visited in an in order traversal of the tree if it exists
int Tree::helpRemoveInOrder(TreeNode* root, int n, TreeNode* parent, bool leftChild, int counter, bool& isDeleted) {
	if (root == nullptr) {
		return counter;
	}
	else {
		if (root->left != nullptr) {
			parent = root;
		}
		counter = helpRemoveInOrder(root->left, n, parent, true, counter, isDeleted);
		if (counter == n && isDeleted == false) {
			reassignPointers(root, parent, leftChild); //delete the node from the tree
			cout << "successful\n";
			isDeleted = true;
			return counter;
		}
		counter++;
		if (root->right != nullptr) {
			parent = root;
		}
		counter = helpRemoveInOrder(root->right, n, parent, false, counter, isDeleted);
	}
	return counter;

}

void Tree::removeInOrder(int N) {
	if (N > (int)this->values.size() || N < 0) {
		cout << "unsuccessful\n";
		return;
	}
	bool temp = false;
	int result = helpRemoveInOrder(this->root, N, this->root, false, 0, temp);
	if (result != (int)this->values.size()) {
		cout << "unsuccessful\n";
	}
}

//function for deleting the passed in root from the tree and reassigning the necessary pointers
void Tree::reassignPointers(TreeNode*& root, TreeNode*& parent, bool isLeftChild) {
	if (root->left == nullptr && root->right == nullptr) { //the root has no children
		if (isLeftChild) {
			parent->left = nullptr;
		}
		else {
			parent->right = nullptr;
		}
		this->values.erase(this->values.find(root->UFID));
		delete root;
	}
	else if (root->left != nullptr && root->right == nullptr) { //the root has one left child
		parent->left = root->left;
		root->left = nullptr;
		this->values.erase(this->values.find(root->UFID));
		delete root;
	}
	else if (root->left == nullptr && root->right != nullptr) { //the root has one right child
		parent->right = root->right;
		root->right = nullptr;
		this->values.erase(this->values.find(root->UFID));
		delete root;
	}
	else { //the root has two children
		TreeNode* successor = findInOrderSuccessor(root, parent);
		root->name = successor->name;
		root->UFID = successor->UFID;
		if (successor->right != nullptr) {
			root->right = successor->right;
			successor->right = nullptr;
		}
		this->values.erase(this->values.find(successor->UFID));
		delete successor;
	}
}

//finds and returns the in-order successor of the passed in root
Tree::TreeNode* Tree::findInOrderSuccessor(TreeNode* root, TreeNode*& parent) {
	if (root->right != nullptr) {
		parent = root;
		root = root->right;
		while (root->left != nullptr) { //going all the way left in the right subtree
			parent = root;
			root = root->left;
		}
		if (root->right == nullptr) { //reassigning the parent pointer since parent is passed by reference
			parent->left = nullptr;
		}
		return root;
	}
	else {
		return root;
	}
}

bool Tree::verifyWord(string name, string id) {
	if (id.length() > 8) {
		return false;
	}
	name.erase(remove(name.begin(), name.end(), '\"'), name.end());
	for (char i : name) {
		if (!isalpha(i) && !isspace(i)) {
			return false;
		}
	}
	return true;
}

void Tree::helpDestruct(TreeNode*& root) {
	if (root->left) {
		helpDestruct(root->left);
	}
	if (root->right) {
		helpDestruct(root->right);
	}
	delete root;
}

void Tree::destruct() {
	if (this->root != nullptr) {
		helpDestruct(this->root);
	}
}