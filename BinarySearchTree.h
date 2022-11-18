#include <iostream>
#include <vector>
#include <string>

//Node Class   
//namespace BST {
    class Node {
        public:
            int key;
            std::string value;
            std::string getValue();
            int getKey();
            void setValue(std::string value);
            void setKey(int key);
            Node();
            ~Node();
            Node(int key, std::string value);
            Node *left, *right;
    };

    //BST Class
    class BinarySearchTree {
        public:      
            Node *root;
            BinarySearchTree();
            BinarySearchTree(int key, std::string value);
            ~BinarySearchTree();
            void insert(int key, std::string value);
            std::vector<Node*> search(int key);
            void remove(int key);
            void inorder(Node* traverse);
            Node* findMin(Node* root);
            void print();
            void lookup(int key);
    };
//}



