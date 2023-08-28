#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <regex>
#include <algorithm>
#pragma once

using namespace std;

struct Node {
    string name;
    int ufID;
    int height;
    Node* left;
    Node* right;
    Node(): name(""), ufID(0), height(0), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    Node* insertHelper(Node* root, string name, int ufID);
    Node* printInOrderHelper(Node* root, vector<string>& names);
    Node* printPreOrderHelper(Node* root, vector<string>& names);
    Node* printPostOrderHelper(Node* root, vector<string>& names);
    Node* searchHelper(Node* node, string name, vector<string>& duplicates);
    Node* searchHelper(Node* node, int ufID);
    Node* findParent(int ufID);
    bool removeHelper(Node* node, int ufID);
    bool removeInorderHelper(int N);
public:
    Node* root;
    AVLTree() : root(nullptr) {}
    vector<int> inOrder;

    int getBalance(Node* node);
    int getHeight(Node* node);
    void printLevelCount();
    void insert(string name, int ufID);
    void printInorder();
    void printPreorder();
    void printPostorder();
    string search(int ufID);
    void search(string name);
    void remove(int ufID);
    void removeInorder(int N);

    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* rotateRightLeft(Node* node);
};