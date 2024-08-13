#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class AVLTree {
    private:
        struct Node {
            string name;
            string ufid;
            Node* left;
            Node* right;
            int height;

            Node() {
                name = "";
                ufid = "";
                left = nullptr;
                right = nullptr;
                height = 1;
            }
        };

        Node* root;   // points to the root node of the AVL Tree

        int getHeight(Node* root) {
            if (root == nullptr)
                return 0;
            return root->height;
        }

        Node* insertHelper(Node* root, string name, string ufid) {
            if (root == nullptr) {
                Node* newNode = new Node();
                newNode->name = name;
                newNode->ufid = ufid;
                root = newNode;
                cout << "successful" << endl;
                return root;
            }
            else if (ufid == root->ufid) {
                cout << "unsuccessful" << endl;
                return root;
            }
            else if (ufid < root->ufid) {
                root->left = insertHelper(root->left, name, ufid);
            }
            else if (ufid > root->ufid) {
                root->right = insertHelper(root->right, name, ufid);
            }

            // Update the height of the current node
            root->height = 1 + max(getHeight(root->left), getHeight(root->right));
            // calcBF(root);
            int balanceFactor = getHeight(root->left) - getHeight(root->right);
            // balanceTree(root);

            if (balanceFactor > 1) {
                // Left heavy
                if (ufid < root->left->ufid) {
                    // Left-Left case
                    return rotateRight(root);
                } else {
                    // Left-Right case
                    root->left = rotateLeft(root->left);
                    return rotateRight(root);
                }
            } else if (balanceFactor < -1) {
                // Right heavy
                if (ufid > root->right->ufid) {
                    // Right-Right case
                    return rotateLeft(root);
                } else {
                    // Right-Left case
                    root->right = rotateRight(root->right);
                    return rotateLeft(root);
                }
            }

            return root;
        }

        Node* printInorderHelper(Node* root, bool& shift1) {
            if (root == nullptr)
                return root;
            root->left = printInorderHelper(root->left, shift1);
            if (!shift1)
                cout << ", ";
            else
                shift1 = false;
            cout << root->name;
            root->right = printInorderHelper(root->right, shift1);
            return root;
        }

        Node* printPreorderHelper(Node* root, bool& shift2) {
            if (root == nullptr)
                return root;
            if (!shift2)
                cout << ", ";
            else
                shift2 = false;
            cout << root->name;
            root->left = printPreorderHelper(root->left, shift2);
            root->right = printPreorderHelper(root->right, shift2);
            return root;
        }

        Node* printPostorderHelper(Node* root, bool& shift3) {
            if (root == nullptr)
                return root;
            root->left = printPostorderHelper(root->left, shift3);
            root->right = printPostorderHelper(root->right, shift3);
            if (!shift3)
                cout << ", ";
            else
                shift3 = false;
            cout << root->name;
            return root;
        }

        Node* searchIDHelper(Node* root, string ID, bool& found) {
            if (root == nullptr)
                return root;
            if (ID == root->ufid) {
                cout << root->name << endl;
                found = true;
                return root;
            }
            else if (ID > root->ufid)
                root->right = searchIDHelper(root->right, ID, found);
            else if (ID < root->ufid)
                root->left = searchIDHelper(root->left, ID, found);
            return root;
        }

        Node* searchNameHelper(Node* root, string name, bool& exist) {
            if (root == nullptr)
                return root;
            if (name == root->name) {
                exist = true;
                cout << root->ufid << endl;
            }
            root->left = searchNameHelper(root->left, name, exist);
            root->right = searchNameHelper(root->right, name, exist);
            return root;
        }

// <<<================================= One Day Break ====================================>>> \\

        Node* rotateRight(Node* root) {
            Node* newRoot = root->left;
            root->left = newRoot->right;
            newRoot->right = root;

            root->height = 1 + max(getHeight(root->left), getHeight(root->right));
            newRoot->height = 1 + max(getHeight(root->left), getHeight(root->right));

            return newRoot;
        }

        Node* rotateLeft(Node* root) {
            Node* newRoot = root->right;
            root->right = newRoot->left;
            newRoot->left = root;

            root->height = 1 + max(getHeight(root->left), getHeight(root->right));
            newRoot->height = 1 + max(getHeight(root->left), getHeight(root->right));

            return newRoot;
        }

        Node* removeIDHelper(Node *root, string ufid, bool &removed) {
            if (root == nullptr)
                return root;
            else if (ufid == root->ufid) {
                removed = true;
                // there are 3 cases (no child) (1 child) (2 child)
                if (root->right == nullptr && root->left == nullptr) {
                    delete root;
                    return nullptr;
                }
                else if (root->left == nullptr && root->right != nullptr) {
                    Node* connect = root->right;
                    delete root;
                    return connect;
                }
                else if (root->left != nullptr && root->right == nullptr) {
                    Node* connect = root->left;
                    delete root;
                    return connect;
                }
                else if (root->left != nullptr && root->right != nullptr) {
                    Node* swapper = inorderSuccessor(root->right);

                    root->ufid = swapper->ufid;
                    root->name = swapper->name;

                    root->right = removeIDHelper(root->right, swapper->ufid, removed);
                }
            }
            else if (ufid < root->ufid) {
                root->left = removeIDHelper(root->left, ufid, removed);
            }
            else if (ufid > root->ufid) {
                root->right = removeIDHelper(root->right, ufid, removed);
            }
            return root;
        }

        Node* inorderSuccessor(Node* root) {
            while (root->left != nullptr) {
                if (root->left == nullptr) {
                    return root;
                }
                root = root->left;
            }
            return root;
        }

        Node* removeInorderHelper(Node* root, int index, int& count, bool& good) {
            if (root == nullptr)
                return root;
            root->left = removeInorderHelper(root->left, index, count, good);

            count += 1;
            if (count == index) {
                // then call the remove function.
                root = removeIDHelper(root, root->ufid, good);
                good = true;
                return root;
            }
            root->right = removeInorderHelper(root->right, index, count, good);
            return root;
        }

        Node* viewHeight(Node* root) {
            if (root == nullptr)
                return root;
            cout << root->height << ", ";
            viewHeight(root->left);
            viewHeight(root->right);
            return root;
        }

        int BFS(Node* root) {
            if (root == nullptr)
                return 0;

            vector<Node*> currentLevel;
            vector<Node*> nextLevel;
            int levels = 0;

            currentLevel.push_back(root);

            while (!currentLevel.empty()) {
                Node* currentNode = currentLevel.front();
                currentLevel.erase(currentLevel.begin());

                if (currentNode->left)
                    nextLevel.push_back(currentNode->left);
                if (currentNode->right)
                    nextLevel.push_back(currentNode->right);

                if (currentLevel.empty()) {
                    levels++;
                    swap(currentLevel, nextLevel);
                }
            }
            return levels;
        }

    public:
        // Constructor
        AVLTree() {
            root = nullptr;
        }

        // recursive Destructor
        ~AVLTree() {
            clear(root);
        }

        void clear(Node* node) {
            if (node != nullptr){
                clear(node->left);
                clear(node->right);
                delete node;
            }
        }

        void insertNAMEID(string name, string ufid) {
            this->root = insertHelper(this->root, name, ufid);
        }

        void printInorder() {
            bool shift1 = true;
            this->root = printInorderHelper(this->root, shift1);
            cout << endl;
        }

        void printPreorder() {
            bool shift2 = true;
            this->root = printPreorderHelper(this->root, shift2);
            cout << endl;
        }

        void printPostorder() {
            bool shift3 = true;
            this->root = printPostorderHelper(this->root, shift3);
            cout << endl;
        }

        void searchID(string ID) {
            bool found = false;
            this->root = searchIDHelper(this->root, ID, found);
            if (!found)
                cout << "unsuccessful" << endl;
        }

        void searchName(string name) {
            bool exist = false;
            this->root = searchNameHelper(this->root, name, exist);
            if (!exist)
                cout << "unsuccessful" << endl;
        }

        void viewHeight() {
            this->root = viewHeight(this->root);
            cout << endl;
        }

        void removeID(string ufid) {
            bool removed = false;
            this->root = removeIDHelper(this->root, ufid, removed);
            if (!removed)
                cout << "unsuccessful" << endl;
            else {
                cout << "successful" << endl;
            }
        }

        void removeInorder(int index) {
            int count = -1;
            bool good = false;
            this->root = removeInorderHelper(this->root, index, count, good);
            if (!good)
                cout << "unsuccessful" << endl;
            else {
                cout << "successful" << endl;
            }
            // there is a case where if there are no nodes in the tree then no nth inOrder removal.
        }

        int printLevelCount() {
            int level = BFS(this->root);
            return level;
        }
};