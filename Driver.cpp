#include "BinarySearchTree.h"
//#include <chrono>
#include <vector>
#include <iostream>
#include <pthread.h>
#include <fstream>
#include <string>

using namespace std;

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_cond = PTHREAD_COND_INITIALIZER;

/**
 * @brief     A simple struct used to pass data to the threads
 *
 *
 */
typedef struct threadArgs
{
    BinarySearchTree *tree;
    string *in;

    
} threadArgs;

/**
 * @brief Takes a C-Style string and parses it into readable string instructions.
 *
 * @param line A C-Style String.
 * @return vector<string> Instructions parsed from the line.
 */
vector<string> processLine(string line)
{
    vector<string> ret;
    int size = line.length();
    string temp = "";
    for (int i = 0; i < size; i++)
    {
        if (line[i] != ' ' && line[i] != '\"')
        {
            string s(1, line[i]);
            temp += s;
        }
        else if (line[i] == '\"')
        {
            continue;
        }
        else
        {
            ret.push_back(temp);
            temp = "";
        }
    }
    ret.push_back(temp);
    if (ret.size() == 2)
    {
        ret.push_back("Null Val");
    }
    return ret;
}

// TODO: Create a lock system and a thread organization system.
void *threadRunner(void *args)
{
    // Cast the void pointer to a threadArgs struct, then take all needed values from there
    threadArgs *tArgs = (threadArgs *)args;
    BinarySearchTree *tree = tArgs->tree;
    string in = *tArgs->in;

    // Process the input
    vector<string> instructions = processLine(in);
    string directive = instructions[0];
    int key = stoi(instructions[1]);
    string value = instructions[2];

    pthread_mutex_lock(&condition_mutex);
    // Check the first instruction
    if (directive == "I")
    {
        // Insert the key and value
        tree->insert(key, value);
    }
    else if (directive == "D")
    {
        // Delete the key
        tree->remove(key);
    }
    else if (directive == "L")
    {
        // Search for the key
        tree->lookup(key);
    }
    pthread_mutex_unlock(&condition_mutex);
}

int main()
{
    //auto start = chrono::steady_clock::now();
    // Init Vars
    string fileName;
    string line;
    int numThreads;
    vector<string> instructions;
    BinarySearchTree BinTree = BinarySearchTree();
    vector<pthread_t> threads;

    string directive;
    int key;
    string value;

    //  TODO: uncomment these 2 lines!
    //  cout << "Enter the name/path of the file: ";
    //  cin >> fileName;
    fileName = "testFile.txt";
    ifstream myFile(fileName);

    if (myFile.is_open() && myFile.good())
    {
        // Get the number of threads
        getline(myFile, line);
        instructions = processLine(line);
        if (instructions[0] == "N")
        {
            numThreads = stoi(instructions[1]);
            cout << "Using " << numThreads << " threads." << endl;
        }
        else
        {
            cout << "Error: First line of file must be N <numThreads>" << endl;
            return 1;
        }
    }

    // First line has been processed, let's start our multithreaded process
    threadArgs *args = new threadArgs;
    if (myFile.is_open())
    {
        while (myFile.good())
        {
            // Create N threads
            for (int i = 0; i < numThreads; i++)
            {
                // Since we're taking multiple lines at a time, we'll need to verify the file is still open each time we pull a line
                if (myFile.good())
                {
                    getline(myFile, line);
                    // Make a struct for the new threads
                    args->tree = &BinTree;
                    args->in = &line;

                    threads.push_back(pthread_t());
                    pthread_create(&threads[i], NULL, *threadRunner, (void*) args);
                    // pthread_join(threads[i], NULL);
                }
                else
                {
                    continue;
                }
                for(int i = 0; i < threads.size(); i++)
                {
                    pthread_join(threads[i], NULL);
                }
            }
        }
    }

    // Old single threaded code
    /*
    // If the directive is an I (Insert), Insert the key and value given on that line into the BST
    else if (directive == "I")
    {
        BinTree.insert(key, value);
    }
    // If the directive is D (Delete), Delete the key given on that line
    else if (directive == "D")
    {
        BinTree.remove(key);
    }
    // If the directive is L (Lookup/Search), Lookup the key given on that line
    else if (directive == "L")
    {
        BinTree.lookup(key);
    }
    else
    {
        std::cout << "directive not recognized!" << endl;
    }
}
*/
    // Close the file
    myFile.close();
    //auto end = chrono::steady_clock::now();
    //auto diff = end - start;
    //cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;
    return 0;
}
