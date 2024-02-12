#include <iostream>
#include <sstream>
#include <algorithm>
#include "Tree.h"

int main() {
    Tree tree;
    string line;
    getline(cin, line);
    int numCommands = stoi(line); //getting the number of times to run the for loop
    for (int i = 0; i < numCommands; i++) {
        getline(cin, line);
        istringstream in(line);
        string command;
        string name, id, temp;
        getline(in, command, ' ');
        if (command == "insert") { //verify the name and id values
            getline(in, temp, '\"');
            getline(in, name, '\"');
            getline(in, temp, ' ');
            getline(in, id, ' ');
            if (tree.verifyWord(name, id)) {
                name.erase(remove(name.begin(), name.end(), '\"'), name.end());
                tree.insert(id, name);
            }
            else {
                cout << "unsuccessful\n";
                continue;
            }
        }
        else if (command == "remove") {
            getline(in, id, ' ');
            tree.removeID(id);
        }
        else if (command == "search") {
            string next;
            bool isNumber = true;
            getline(in, temp, '\"'); //if temp is non-empty, the next word is an id
            getline(in, next, '\"'); //if next is non-empty, the next word is a name
            for (char i : temp) { //checking to see if temp is a valid number
                if (!isdigit(i)) {
                    isNumber = false;
                    break;
                }
            }
            if (!temp.empty() && isNumber) {
                tree.searchID(temp);
            }
            else if (!next.empty()) {
                tree.searchName(next);
            }
            else {
                cout << "unsuccessful\n";
                continue;
            }
        }
        else if (command == "printInorder") {
            tree.printInOrder();
        }
        else if (command == "printPreorder") {
            tree.printPreOrder();
        }
        else if (command == "printPostorder") {
            tree.printPostOrder();
        }
        else if (command == "printLevelCount") {
            tree.printLevelCount();
        }
        else if (command == "removeInorder") {
            getline(in, id, ' ');
            int nVal = stoi(id);
            tree.removeInOrder(nVal);
        }
        else {
            cout << "unsuccessful\n";
        }
    }
    tree.destruct(); //destruction of the tree to avoid memory leaks
    return 0;
}

