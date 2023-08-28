#include "AVL.h"

// Citing Lisha Zhou: Stepik 5.1.1
// Citing Amanpreet Kapoor: Stepik 5.2.2

int AVLTree::getHeight(Node* node) { // returns the height of the tree given a node
    if (node == nullptr) {
        return -1;
    }
    int nodeHeight = 1 + max(node->left ? node->left->height : -1, node->right ? node->right->height: -1);
    return nodeHeight;
}

int AVLTree::getBalance(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return leftHeight - rightHeight;
}

Node* AVLTree::findParent(int ufID) {
    Node* parent = nullptr;
    Node* curr = root;
    while (curr != nullptr && curr->ufID != ufID) {
        parent = curr;
        if (ufID < curr->ufID) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    return parent;
}

string AVLTree::search(int ufID) {
    Node* toFind = searchHelper(this->root, ufID);
    if (toFind != nullptr) {
        return toFind->name;
    }
    else {
        return "unsuccessful";
    }
}

Node* AVLTree::searchHelper(Node* node, int ufID) {  // search function by ID
    if (node == nullptr || node->ufID == ufID) {
        return node;
    }
    if (node->ufID < ufID) {  // search right subtree
        return searchHelper(node->right, ufID);
    }
    else {
        return searchHelper(node->left, ufID); // search left subtree
    }
}

void AVLTree::search(string name) {
    vector<string> ID;
    Node* toFind = searchHelper(this->root, name, ID);
    if (toFind != nullptr) {
        for (auto i : ID) {
            cout << i << endl;
        }
    }
    if (ID.empty()) {
        cout << "unsuccessful" << endl;
    }
}

Node* AVLTree::searchHelper(Node* node, string name, vector<string>& duplicates) { // Search function by name
    if (node != nullptr) {
        if (node->name == name) {
            string leadingZeros = to_string(node->ufID);
            if (leadingZeros.length() != 8) { // ID already valid, add leading zeros if needed
                string ID = string(8 - leadingZeros.length(), '0') + leadingZeros;
                duplicates.push_back(ID);
            }
            else {
                duplicates.push_back(leadingZeros);
            }
        }
        searchHelper(node->left, name, duplicates);
        searchHelper(node->right, name, duplicates);
        return node;
    }
    return node;
}

void AVLTree::remove(int ufID) {
    bool removed = removeHelper(this->root, ufID);
    if (removed) {
        cout << "successful" << endl;
        sort(inOrder.begin(), inOrder.end());
        for (int i = 0; i < inOrder.size(); i++) {  // remove value from vector
            if (inOrder[i] == ufID) {
                inOrder.erase(inOrder.begin() + i);
            }
        }
    }
    else {
        cout << "unsuccessful" << endl;
    }
}

bool AVLTree::removeHelper(Node *node, int ufID) {
    Node* child = searchHelper(node, ufID); // node to remove
    Node* parent = findParent(ufID); // parent of child

    if (child == nullptr) {  // ID not found
        return false;
    }
    if (parent == nullptr) {
        parent = child;
    }

    if (child->left == nullptr && child->right == nullptr) { // no children
        if (parent->ufID < child->ufID) {  // go to right subtree
            parent->right = nullptr;
        }
        else {
            parent->left = nullptr;  // go to left subtree
        }
        delete child;
        parent->height = getHeight(parent);
        this->root->height = getHeight(root); // update entire tree height
        return true;
    }

    else if (child->left != nullptr && child->right != nullptr) { // two children
        Node* parentSuccessor = nullptr;
        Node* successor = child->right;

        while (successor->left != nullptr) {  // gets leftmost node of right subtree
            parentSuccessor = successor;
            successor = successor->left;
        }

        if (child == root) {
            root = successor;
        }
        else if (parent->ufID < child->ufID) {
            parent->right = successor;
        }
        else {
            parent->left = successor;
        }
        successor->left = child->left; // preserves original left subtree

        if (parentSuccessor != nullptr) {
            parentSuccessor->left = successor->right;
            successor->right = child->right;
        }
        delete child;
        successor->height = getHeight(successor);
        this->root->height = getHeight(root); // update entire tree height
        return true;
    }
    else {
        if (parent->ufID < child->ufID) {  // one child
            if (child->left != nullptr) {
                parent->right = child->left;
            }
            else {
                parent->right = child->right;
            }
        }
        else {
            if (child->left != nullptr) {
                parent->left = child->left;
            } else {
                parent->left = child->right;
            }
        }

        delete child;
        parent->height = getHeight(parent);
        this->root->height = getHeight(root); // update entire tree height
        return true;
    }
}

void AVLTree::removeInorder(int N) {
    if (removeInorderHelper(N)) {
        cout << "successful" << endl;
        sort(inOrder.begin(), inOrder.end());
        for (int i = 0; i < inOrder.size(); i++) {  // remove value from vector
            if (i == N) {
                inOrder.erase(inOrder.begin() + i);
            }
        }
    }
    else {
        cout << "unsuccessful" << endl;
    }
}

bool AVLTree::removeInorderHelper(int N) {
    sort(inOrder.begin(), inOrder.end());
    if(N > inOrder.size()) {
        return false;
    }
    int ID = inOrder[N]; // find ID by index N in vector
    Node* toRemove = searchHelper(root, ID);
    bool success = removeHelper(toRemove, toRemove->ufID);
    return success;
}

void AVLTree::insert(string name, int ufID) {
    this->root = insertHelper(this->root, name, ufID);
    if (root != nullptr) {
        cout << "successful" << endl;
    }
    else {
        cout << "unsuccessful" << endl;
    }
}

Node* AVLTree::insertHelper(Node* root, string name, int ufID) {
    if (root == nullptr) {
        root = new Node();
        root->name = name;
        root->ufID = ufID;
        inOrder.push_back(root->ufID);
        return root;
    }

    if (ufID < root->ufID) {
        root->left = insertHelper(root->left, name, ufID);
    }
    else if (ufID > root->ufID) {
        root->right = insertHelper(root->right, name, ufID);
    }
    else {
        return root; // ufID equal to root ufID
    }

    // update height
    root->height =  getHeight(root);
    if (getBalance(root) < -1) { // Right Heavy
        if (getBalance(root->right) < 0) {
            root = rotateLeft(root);  // Left Rotation
        }
        else if (getBalance(root->right) > 0) {
            root = rotateRightLeft(root);  // Right-Left Rotation
        }
    }
    else if (getBalance(root) > 1) { // Left Heavy
        if (getBalance(root->left) > 0) {
            root = rotateRight(root);  // Right Rotation
        }
        else if (getBalance(root->left) < 0)  {
            root = rotateLeftRight(root);  // Left-Right Rotation
        }
    }
    return root;
}

Node* AVLTree::rotateLeft(Node* node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;
    // Update height of node and root

    node->height = getHeight(node);
    rightChild->height = getHeight(rightChild);
    return rightChild;
}

Node* AVLTree::rotateRight(Node *node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;
    // Update height of node and root

    node->height = getHeight(node);
    leftChild->height = getHeight(leftChild);
    return leftChild;
}

Node* AVLTree::rotateLeftRight(Node *node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

Node* AVLTree::rotateRightLeft(Node *node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

void AVLTree::printInorder() {
    vector<string> names;
    this->root = printInOrderHelper(this->root, names);
    for (int i = 0; i < names.size(); i++) {
        cout << names[i];
        if (i != names.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
}

Node* AVLTree::printInOrderHelper(Node* root, vector<string>& names) {
    if (root != nullptr) {
        printInOrderHelper(root->left, names);
        names.push_back(root->name);
        printInOrderHelper(root->right, names);
        return root;
    }
}

void AVLTree::printPreorder() {
    vector<string> names;
    this->root = printPreOrderHelper(this->root, names);
    for (int i = 0; i < names.size(); i++) {
        cout << names[i];
        if (i != names.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
}

Node* AVLTree::printPreOrderHelper(Node *root, vector<string>& names) {
    if (root != nullptr) {
        names.push_back(root->name);
        printPreOrderHelper(root->left, names);
        printPreOrderHelper(root->right, names);
        return root;
    }
}

void AVLTree::printPostorder() {
    vector<string> names;
    this->root = printPostOrderHelper(this->root, names);
    for (int i = 0; i < names.size(); i++) {
        cout << names[i];
        if (i != names.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
}

Node *AVLTree::printPostOrderHelper(Node *root, vector<string>& names) {
    if (root != nullptr) {
        printPostOrderHelper(root->left, names);
        printPostOrderHelper(root->right, names);
        names.push_back(root->name);
        return root;
    }
}

void AVLTree::printLevelCount() {
    if (this->root == nullptr) {
        cout << "0" << endl;
    }
    else {
        int level = getHeight(this->root) + 1;
        cout << level << endl;
    }
}

