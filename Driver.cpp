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
    int size = line.length();
    string temp = "";
    for(int i = 0; i < size; i++) {   
        if (line[i] != ' ' && line[i] != '\"') {
            string s(1, line[i]);
            temp += s;
        }
        else if (line[i] == '\"') {
            continue;
        }
        else {
            ret.push_back(temp);
            temp = "";
        }
    }

        ret.push_back(temp);
        return ret;
}



int main() {
    // Init Vars
    string fileName;
    string line;
    int numThreads;
    vector<string> instructions;
    BinarySearchTree BinTree = BinarySearchTree();

    //Take File Name as Input, Might need to make this a function for multithreaded usage.
    // TODO: uncomment these 2 lines!
    // cout << "Enter the name/path of the file: ";
    // cin >> fileName;
    fileName = "testFile.txt";
    ifstream myFile(fileName);
    if(myFile.is_open()) {
        while(myFile.good()) {
            getline(myFile, line);
            instructions = processLine(line);

            // Convert instruction line to vars for easier reading
            string directive = instructions[0];
            int key = stoi(instructions[1]);
            string value = "";
            if (instructions.size() > 2) {
                value = instructions[2];
            }
            // If the directive is N (Num. Threads), then create N threads to run the process
            if (directive == "N") {
                if (key < 1) {
                    std::cout << "Cannot have 0 or less threads!" << endl;
                }
                else {
                    numThreads = key;
                    std::cout << "Using " << numThreads << " threads." << endl;
                }
            }
            // If the directive is an I (Insert), Insert the key and value given on that line into the BST
            else if (directive == "I") {
                BinTree.insert(key, value);
            }
            // If the directive is D (Delete), Delete the key given on that line
            else if (directive == "D") {
                BinTree.remove(key);
            }
            // If the directive is L (Lookup/Search), Lookup the key given on that line
            else if (directive == "L") {
                BinTree.lookup(key);
            }
            else {
                std::cout << "directive not recognized!" << endl;
            }
        }
        myFile.close();
        std::cout << "Done!" << endl;
    }
    


    // BinTree.print();
    //test.remove(0);
    return 0;
}
