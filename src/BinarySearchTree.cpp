#include <iostream>
#include <vector>
#include <string>

using namespace std;

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


};

//Default Constructor
BinarySearchTree::BinarySearchTree() {
    root = NULL;
}

//Parametrized Constructor
BinarySearchTree::BinarySearchTree(int key, string value) {
    root = new Node(key, value);
}

BinarySearchTree::~BinarySearchTree() {
    delete root;
}

//Takes a value, finds and deletes from BST, then rearranges (If nessecary)
void BinarySearchTree::remove(int key) {
    if (root == NULL) {
        cout << "Tree is empty, cannot remove" << endl;
        return;
    }
    vector<Node*> traverse = search(key);
    Node* pivot = traverse[traverse.size() - 1];
    Node* parent = traverse[traverse.size() - 2];
    int tempHolder = 0;

    //If the value is not in the tree
    if (pivot->getKey() != key) {
        cout << "Value not in tree" << endl;
        return;
    }
    // No Leaves
    else if (pivot -> left == NULL && pivot -> right == NULL) {
        if(pivot -> key < parent -> key) {
            parent -> left = NULL;
        }
        else { parent -> right = NULL; }
        delete pivot;
    }
    // 1 Leaf
    else if (pivot -> left == NULL && pivot -> right != NULL) {
        tempHolder = pivot -> right -> key;
        remove(tempHolder);
        pivot -> key = tempHolder;
    }
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
    
}

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
    if (root = NULL) {
        root = new Node(key, value);
        return;
    }
    Node* currNode = root;
    bool search = true;
    //BinarySearchTree me = *this;
    while (search) {
        if (key < currNode -> key) {
            if (currNode -> left != NULL) {
                currNode = currNode -> left;
                continue;
            }
            currNode -> left = new Node(key, value);
            search = false;
        }
        if (key > currNode -> key) {
            if (currNode -> right != NULL) {
                currNode = currNode -> right;
                continue;
            }
            currNode -> right = new Node(key, value);
            search = false;
        }
    }  
}

//Traverse BST using def of BST (i.e left is less, right is more, etc.)
vector<Node*> BinarySearchTree::search(int key) {
    Node* currNode = root;
    bool search = true;
    vector<Node*> nodeTraverse;
    if (root == NULL) {
        cout << "Tree is empty" << endl;
        return nodeTraverse;
    }
    while (search) {
        nodeTraverse.push_back(currNode);
        if (key < currNode -> key) {
            if (currNode -> left != NULL) {
                currNode = currNode -> left;
                continue;
            }
            else {
                search = false;
            };
        }
        else if (key > currNode -> key) {
            if (currNode -> right != NULL) {
                currNode = currNode -> right;
                continue;
            }
            else {
                search = false;
            }
        }
        else { search = false; } 
    }  
    return nodeTraverse;
}

void BinarySearchTree::print() {
    cout << "Printing Tree (In Order!)\n";
    inorder(root);
}

void BinarySearchTree::inorder(Node* traverse) {
    if(traverse == NULL) {
        return;
    }
    inorder(traverse -> left);
    cout << "Node Value: " << traverse -> value << " \n";
    inorder(traverse -> right);
}