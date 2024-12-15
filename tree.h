#ifndef LR2_TREE_H
#define LR2_TREE_H

int minVal = -999999;
int maxVal = 999999;

struct TNode {
    int value;
    TNode* left;
    TNode* right;

    TNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

struct BinarySearchTree {
    TNode* root;

    BinarySearchTree() : root(nullptr) {}

    void insert(int val);
    bool search(int val) const;
    bool isBST() const;


    TNode* insertNode(TNode* node, int val);
    TNode* searchNode(TNode* node, int val) const;
    bool isBinartSearch(TNode *currentNode, int minValue, int maxValue) const;
};


void BinarySearchTree::insert(int val) {
    root = insertNode(root, val);
}

TNode* BinarySearchTree::insertNode(TNode* node, int val) {
    if (!node) {
        return new TNode(val);
    }

    if (val < node->value) {
        node->left = insertNode(node->left, val);
    } else if (val > node->value) {
        node->right = insertNode(node->right, val);
    }

    return node;
}

bool BinarySearchTree::search(int val) const {
    return searchNode(root, val) != nullptr;
}

TNode* BinarySearchTree::searchNode(TNode* node, int val) const {
    if (!node || node->value == val) {
        return node;
    }

    if (val < node->value) {
        return searchNode(node->left, val);
    }

    return searchNode(node->right, val);
}

bool BinarySearchTree::isBinartSearch(TNode* currentNode, int minValue, int maxValue) const {
    if (currentNode == nullptr) {
        return true;
    }

    if (currentNode->value <= minValue || currentNode->value >= maxValue) {
        return false; // находится ли значение текущего узла в допустимых пределах
    }

    bool isLeftValid = isBinartSearch(currentNode->left, minValue, currentNode->value);
    bool isRightValid = isBinartSearch(currentNode->right, currentNode->value, maxValue);

    return isLeftValid && isRightValid;
}

bool BinarySearchTree::isBST() const {
    return isBinartSearch(root, minVal, maxVal);
}


#endif //LR2_TREE_H
