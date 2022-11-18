
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define OK "OK"
#define FAIL "Fail"


//Node Object, need to make the value field a generic
class Node {
    public:
        int key;
        string value;
        string getValue();
        int getKey();
        void setValue(string value);
        void setKey(int key);
        Node();
        ~Node();
        Node(int key, string value);
        Node *left, *right;
};

Node::Node() {
    this->value = "";
    this->key = 0;
    left = right = NULL;
}

Node::Node(int key, string value){
    this->value = value;
    this->key = key;
    left = right = NULL;
}

Node::~Node() {
    delete left;
    delete right;
}

string Node::getValue() {
    return this->value;
}

int Node::getKey() {
    return this->key;
}

void Node::setValue(string value) {
    this-> value = value;
}

void Node::setKey(int key) {
    this->key = key;
}

//BST Object
class BinarySearchTree {
    public:      
        Node *root;
        BinarySearchTree();
        BinarySearchTree(int key, string value);
        ~BinarySearchTree();
        void insert(int key, string value);
        vector<Node*> search(int key);
        void remove(int key);
        void inorder(Node* traverse);
        Node* findMin(Node* root);
        void print();
        void lookup(int key);


};

// Default Constructor
// TODO: Fix default constructor from creating a node that is default to pointing root to null
// Can be done with a Node, just make sure the node's key and value are NULL and check that
BinarySearchTree::BinarySearchTree() {
    root = NULL;
}

//Parametrized Constructor
BinarySearchTree::BinarySearchTree(int key, string value) {
    root = new Node(key, value);
}

// Destructor method
BinarySearchTree::~BinarySearchTree() {
    delete root;
}

//Takes a value, finds and deletes from BST, then rearranges (If nessecary)
//TODO: Fix deletion algorithm
void BinarySearchTree::remove(int key) {
    // If we have an empty tree, fail and return
    if (root == NULL) {
        cout << FAIL << endl;
    }
    // Tree isn't empty! Traverse and grab pivot, parent
    else {
        vector<Node*> traverse = search(key);
        Node* pivot = traverse[traverse.size() - 1];
        Node* parent = traverse[traverse.size() - 2];
        int tempHolder = 0;

        //If the value is not in the tree
        if (pivot->getKey() != key) {
            cout << FAIL << endl;
            return;
        }

        // If the Node is in the tree, handle the removal by case.
        else {
            // No Leaves
            if (pivot -> left == NULL && pivot -> right == NULL) {
                if(pivot -> key < parent -> key) {
                    parent -> left = NULL;
                }
                else { parent -> right = NULL; }
                delete pivot;
            }

            // 1 Leaf (LEFT EMPTY)
            else if (pivot -> left == NULL && pivot -> right != NULL) {
                tempHolder = pivot -> right -> key;
                remove(tempHolder);
                pivot -> key = tempHolder;
            }

            // 1 Leaf (RIGHT EMPTY)
            else if (pivot -> right == NULL && pivot -> left != NULL) {
                tempHolder = pivot -> left -> key;
                remove(tempHolder);
                pivot -> key = tempHolder;
            }

            // 2 Leaves
            else {
                Node* temp = findMin(pivot);
                int smallest = temp -> key;
                //cout << key;
                remove(smallest);
                pivot -> value = smallest;
            }
            // cout << "Ok" << endl;
        }
    }
}

// Finds the minimum value in the BST
Node* BinarySearchTree::findMin(Node* root) {
    if (root -> left == NULL) {
        return root;
    }
    else {
        return findMin(root -> left);
    }
}


//Look for the first pos. open (Traverse tree until hit a null that matches BST def. and then sub out null for the new node)
void BinarySearchTree::insert(int key, string value) {
    // If tree is empty, create a new node at root
    if (root == NULL) {
        this->root = new Node(key, value);
        cout << OK << endl;
    }

    //Otherwise, traverse the tree to find the appropriate insertion spot
    else {
        Node* currNode = root;
        bool search = true;
        //BinarySearchTree me = *this;
        while (search) {
            if (key < currNode -> key) {
                if (currNode -> left != NULL) {
                    currNode = currNode -> left;
                    continue;
                }
                else {
                    currNode -> left = new Node(key, value);
                    cout << OK << endl;
                    search = false;
                }
            }
            if (key > currNode -> key) {
                if (currNode -> right != NULL) {
                    currNode = currNode -> right;
                    continue;
                }
                else {
                    currNode -> right = new Node(key, value);
                    cout << OK << endl;
                    search = false;
                }
            }
            else {
                cout << FAIL << endl;
                search = false;
            }
        }  
    }
}

//Traverse BST using def of BST (i.e left is less, right is more, etc.)
vector<Node*> BinarySearchTree::search(int key) {
    // Start current node at root, create search boolean and traversal vector
    Node* currNode = root;
    bool search = true;
    vector<Node*> nodeTraverse;
    // If tree is empty, node will obviously not be in tree, so return
    if (root == NULL) {
        // cout << "No " << key << endl;
        return nodeTraverse;
    }
    while (search) {
        nodeTraverse.push_back(currNode);
        // If key is less than current nodes key, move left in BST
        if (key < currNode -> key) {
            if (currNode -> left != NULL) {
                currNode = currNode -> left;
                continue;
            }
            // Failure to find key
            else {
                search = false;
                // cout << "No " << key << endl;
            };
        }
        // If key is greater than current nodes key, move right in BST
        else if (key > currNode -> key) {
            if (currNode -> right != NULL) {
                currNode = currNode -> right;
                continue;
            }
            // Failure to find key
            else {
                search = false;
                // cout << "No " << key << endl;
            }
        }
        // Key is found!
        else {
            // cout << currNode -> value << endl; 
            search = false;
        } 
    }  
    return nodeTraverse;
}

// Print tree in order
void BinarySearchTree::print() {
    cout << "Printing Tree (In Order!)\n";
    inorder(root);
}

// Print helper function
void BinarySearchTree::inorder(Node* traverse) {
    if(traverse == NULL) {
        return;
    }
    inorder(traverse -> left);
    cout << "Node Key: " << traverse->key <<  "\nValue: " << traverse->value << " \n";
    inorder(traverse -> right);
}

// Lookup Function (Prints to console, so it doesn't break prior search calls)
void BinarySearchTree::lookup (int key) {
    vector<Node*> traverse = search(key);
    Node* pivot = traverse[traverse.size() - 1];

    //If the value is not in the tree
    if (pivot->getKey() != key) {
        cout << "No " << key << endl;
        return;
    
    }
    else {
        cout << pivot->value << endl;
    }
}