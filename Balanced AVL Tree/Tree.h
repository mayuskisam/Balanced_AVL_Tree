#pragma once
#include <iostream>
#include <string>
#include <unordered_set> //used for storing ID values
using namespace std;

class Tree {
private:
	struct TreeNode { //defining the node structure and its attributes
		string name;
		string UFID;
		TreeNode* left;
		TreeNode* right;
		int heightVal;
		int balanceFactor;
		TreeNode(string x, string y) : UFID(x), name(y), left(nullptr), right(nullptr), heightVal(0), balanceFactor(0) {}
	};

	TreeNode* root = nullptr;
	unordered_set<string> values;
	//printing functions
	void helpPreOrder(TreeNode* root);
	void helpInOrder(TreeNode* root);
	void helpPostOrder(TreeNode* root);
	//insert/removal functions and their helpers like updateHeight, leftRotation, findInOrderSuccessor, etc.
	TreeNode* helpInsert(TreeNode* root, string value, string name);
	int updateHeight(TreeNode*& root);
	int updateBalance(TreeNode*& root);
	void checkBalance(TreeNode*& root);
	bool helpRemoveID(TreeNode* root, string ID, TreeNode* parent, bool leftChild);
	void reassignPointers(TreeNode*& root, TreeNode*& parent, bool isLeftChild);
	int helpRemoveInOrder(TreeNode* root, int n, TreeNode* parent, bool leftChild, int counter, bool& isDeleted);
	TreeNode* findInOrderSuccessor(TreeNode* root, TreeNode*& parent);
	TreeNode* leftRotation(TreeNode* root, TreeNode* child);
	TreeNode* rightRotation(TreeNode* root, TreeNode* child);
	TreeNode* leftRightRotation(TreeNode* root, TreeNode* child);
	TreeNode* rightLeftRotation(TreeNode* root, TreeNode* child);
	//searching functions
	bool helpSearchID(TreeNode* root, string ID);
	bool helpSearchName(TreeNode* root, string name, bool atLeastOne);
	void helpPrintLevels(TreeNode* root);
	//destructor function	
	void helpDestruct(TreeNode*& root);

public:
	//functions from project assignment page
	void printInOrder();
	void printPostOrder();
	void printPreOrder();
	void insert(string ID, string NAME);
	void removeID(string ID);
	void searchID(string ID);
	void searchName(string NAME);
	void printLevelCount();
	void removeInOrder(int N);
	//extra helper functions
	bool verifyWord(string name, string id);
	void destruct();
};

