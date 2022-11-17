#include "BinarySearchTree.h"
#include <vector>
#include <iostream>
#include <pthread.h>
#include <fstream>
#include <string>

using namespace std;

/**
 * @brief Takes a C-Style string and parses it into readable string instructions.
 * 
 * @param line A C-Style String.
 * @return vector<string> Instructions parsed from the line.
 */
vector<string> processLine(string line) {
    vector<string> ret;
    int size = sizeof(line)/sizeof(line[0]);
    string temp = "";
    for(int i = 0; i < size; i++) {   
        if (line[i] != ' ') {
            string s(1, line[i]);
            s += temp;
        }
        else {
            ret.push_back(temp);
            temp = "";
        }
        return ret;
    }
        cout << line;
}



int main() {
    // Init Vars
    string fileName;
    string line;
    int numThreads;
    vector<string> instructions;
    BinarySearchTree BinTree = BinarySearchTree();

    //Take File Name as Input, Might need to make this a function for multithreaded usage.
    cout << "Enter the name/path of the file: ";
    cin >> fileName;
    ifstream myFile(fileName);
    if(myFile.is_open()) {
        while(myFile.good()) {
            myFile >> line;
            instructions = processLine(line);

            // Convert instruction line to vars for easier reading
            string directive = instructions[0];
            int key = stoi(instructions[1]);
            string value = "";
            if (instructions.size() > 2) {
                value = instructions[2];
            }
            if (directive == "N") {
                if (key < 1) {
                    cout << "Cannot have 0 or less threads!" << endl;
                }
                else {
                    cout << "Using " << key << " threads." << endl;
                }
            }
            // If the directive is an N (Node) or an I (Insert), Insert the key and value given on that line into the BST
            if (directive == "I" && value != "") {
                BinTree.insert(key, value);
            }
            // If the directive is D (Delete), Delete the key given on that line
            if (directive == "D") {
                BinTree.remove(key);
            }
            // If the directive is L (Lookup/Search), Lookup the key given on that line
            if (directive == "L") {
                BinTree.search(key);
            }
        }
    }
    


    BinTree.print();
    //test.remove(0);

    BinTree.print();
}
