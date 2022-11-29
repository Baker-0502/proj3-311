
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define OK "OK"
#define FAIL "Fail"

// Node Object, need to make the value field a generic
class Node
{
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

Node::Node()
{
    this->value = "";
    this->key = 0;
    left = right = NULL;
}

Node::Node(int key, string value)
{
    this->value = value;
    this->key = key;
    left = right = NULL;
}

Node::~Node()
{
    delete left;
    delete right;
}

string Node::getValue()
{
    return this->value;
}

int Node::getKey()
{
    return this->key;
}

void Node::setValue(string value)
{
    this->value = value;
}

void Node::setKey(int key)
{
    this->key = key;
}

// BST Object
class BinarySearchTree
{
public:
    Node *root;
    BinarySearchTree();
    BinarySearchTree(int key, string value);
    ~BinarySearchTree();
    void insert(int key, string value);
    vector<Node *> search(int key);
    void remove(int key);
    void inorder(Node *traverse);
    Node *findMin(Node *root);
    void print();
    void lookup(int key);
};

// Default Constructor
BinarySearchTree::BinarySearchTree()
{
    root = NULL;
}

// Parametrized Constructor
BinarySearchTree::BinarySearchTree(int key, string value)
{
    root = new Node(key, value);
}

// Destructor method
BinarySearchTree::~BinarySearchTree()
{
    delete root;
}

// Takes a value, finds and deletes from BST, then rearranges (If nessecary)
// TODO something is causing a seg fault here
// Probably due to large vector creation from search, get rid of the vector and reduce complexity
// TODO: FIX THIS!!!
void BinarySearchTree::remove(int key)
{
    Node* curr = root;
    bool search = true;

    //Find node to delete, set as current node.
    while(curr-> key != key && search)
    {
        if(key < curr->key)
        {
            curr = curr->left;
        }
        else if (curr->key < key)
        {
            curr = curr->right;
        }
        else
        {
            search = false;
        }
    }

    // If the node has no children, delete it
    if(curr->left == NULL && curr->right == NULL)
    {
        free(curr);
    }
    // If the node has one child, replace it with the child
    else if(curr->left == NULL)
    {
        Node* temp = curr;
        curr = curr->right;
        free(temp);
    }
    else if(curr->right == NULL)
    {
        Node* temp = curr;
        curr = curr->left;
        free(temp);
    }
    // If the node has two children, replace it with the smallest value in the right subtree
    else
    {
        // print();
        Node* temp = findMin(curr->right);
        curr->key = temp->key;
        curr->value = temp->value;
        remove(temp->key);
    }

}

// Finds the minimum value in the BST
Node *BinarySearchTree::findMin(Node *pass)
{
    Node *current = pass;
    while (current->left != NULL && current != NULL)
    {
        current = current->left;
    }
    return current;
}

// Look for the first pos. open (Traverse tree until hit a null that matches BST def. and then sub out null for the new node)
void BinarySearchTree::insert(int key, string value)
{
    // If tree is empty, create a new node at root
    if (root == NULL)
    {
        this->root = new Node(key, value);
        cout << OK << endl;
    }

    // Otherwise, traverse the tree to find the appropriate insertion spot
    else
    {
        Node *currNode = root;
        bool search = true;
        // BinarySearchTree me = *this;
        while (search)
        {
            if (key < currNode->key)
            {
                if (currNode->left != NULL)
                {
                    currNode = currNode->left;
                    continue;
                }
                else
                {
                    currNode->left = new Node(key, value);
                    cout << OK << endl;
                    search = false;
                }
            }
            if (key > currNode->key)
            {
                if (currNode->right != NULL)
                {
                    currNode = currNode->right;
                    continue;
                }
                else
                {
                    currNode->right = new Node(key, value);
                    cout << OK << endl;
                    search = false;
                }
            }
            else if (key == currNode->key)
            {
                cout << FAIL << endl;
                search = false;
            }
            else
            {
                search = false;
            }
        }
    }
}

// Traverse BST using def of BST (i.e left is less, right is more, etc.)
vector<Node *> BinarySearchTree::search(int key)
{
    vector<Node *> traverse = {NULL, NULL};
    Node *currNode = root;
    Node *parent = NULL;
    bool search = true;
    while (search)
    {
        if (key < currNode->key)
        {
            if (currNode->left != NULL)
            {
                parent = currNode;
                currNode = currNode->left;
                continue;
            }
            else
            {
                traverse[0] = parent;
                traverse[1] = currNode;
                search = false;
            }
        }
        if (key > currNode->key)
        {
            if (currNode->right != NULL)
            {
                parent = currNode;
                currNode = currNode->right;
                continue;
            }
            else
            {
                traverse[0] = parent;
                traverse[1] = currNode;
                search = false;
            }
        }
        else if (key == currNode->key)
        {
            traverse[0] = parent;
            traverse[1] = currNode;
            search = false;
        }
        else
        {
            search = false;
        }
    }
    return traverse;
}

// Print tree in order
void BinarySearchTree::print()
{
    cout << "Printing Tree (In Order!)\n";
    inorder(root);
}



// Print helper function
void BinarySearchTree::inorder(Node *traverse)
{
    if (traverse == NULL)
    {
        return;
    }
    inorder(traverse->left);
    cout << "Node Key: " << traverse->key << "\nValue: " << traverse->value << " \n";
    inorder(traverse->right);
}

// Lookup Function (Prints to console, so it doesn't break prior search calls)
void BinarySearchTree::lookup(int key)
{
    vector<Node *> traverse = search(key);
    Node *pivot = traverse[1];

    // If the value is not in the tree
    if (pivot->getKey() != key)
    {
        cout << "No " << key << endl;
        return;
    }
    else
    {
        cout << pivot->value << endl;
    }
}