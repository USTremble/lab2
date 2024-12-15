#ifndef LR2_CBT_H
#define LR2_CBT_H

struct TreeNode {
    int value;
    TreeNode* right;
    TreeNode* left;

    TreeNode(const int val) : value(val), left(nullptr), right(nullptr) {}
};

struct CompleteBinaryTree {
    TreeNode* root;
    CompleteBinaryTree() : root(nullptr) {}

    void insert(int val);
    void DFS();
    string serialize();
    void deserialize(string data);
    bool search(int val);
    bool isComplete();
    void printTree();
    void printNode(TreeNode* node, string prefix, bool isLeft);

    bool isCompleteBinaryTree(TreeNode* node);
};

void CompleteBinaryTree::insert(int val) {
    if (!root) {
        root = new TreeNode(val);
        return;
    }

    Queue<TreeNode*> q;
    q.enqueue(root); // добавляем корень

    while (q.size() > 0) {
        TreeNode* current = q.dequeue();

        if (!current->left) {
            current->left = new TreeNode(val);
            return;
        } else {
            q.enqueue(current->left); // добавляем в очередь
        }

        if (!current->right) {
            current->right = new TreeNode(val);
            return;
        } else {
            q.enqueue(current->right);
        }
    }
}

void CompleteBinaryTree::DFS() {
    if (!root) {
        return;
    }

    Stack<TreeNode*> stack;
    stack.push(root);

    while (stack.size() > 0) {
        TreeNode* current = stack.pop();

        cout << current->value << " ";

        if (current->right) {
            stack.push(current->right);
        }
        if (current->left) {
            stack.push(current->left);
        }
    }
    cout << endl;
}

bool CompleteBinaryTree::search(int val) {
    if (!root) {
        return false;
    }

    Queue<TreeNode*> q;
    q.enqueue(root);

    while (q.size() > 0) {
        TreeNode* current = q.dequeue();

        if (current->value == val) {
            return true;
        }

        if (current->left) {
            q.enqueue(current->left);
        }
        if (current->right) {
            q.enqueue(current->right);
        }
    }

    return false;
}


bool CompleteBinaryTree::isCompleteBinaryTree(TreeNode* root) {
    if (!root) {
        return true;
    }

    Queue<TreeNode*> q;
    q.enqueue(root);
    bool isFoundEmpty = false;

    while (q.size() > 0) {
        TreeNode* current = q.dequeue();

        if (current) {
            if (isFoundEmpty) {
                return false; // узел после пустого нарушает порядок
            }
            q.enqueue(current->left);
            q.enqueue(current->right);
        } else {
            isFoundEmpty = true; // найден первый пустой узел
        }
    }

    return true;
}


bool CompleteBinaryTree::isComplete() {
    return isCompleteBinaryTree(root);
}

string CompleteBinaryTree::serialize() {
    if (!root) {
        return "";
    }

    string result;
    Queue<TreeNode*> q;
    q.enqueue(root);

    while (q.size() > 0) {
        TreeNode* current = q.dequeue();

        if (current) {

            if (!result.empty()) {
                result += ',';
            }
            result += to_string(current->value);

            if (current->left) { // добавляем только непустые узлы в очередь
                q.enqueue(current->left);
            }
            if (current->right) {
                q.enqueue(current->right);
            }
        }
    }

    return result;
}

void CompleteBinaryTree::deserialize(string str) {
    if (str.empty()) {
        root = nullptr;
        return;
    }

    Array<string> elements = split(str, ',');
    if (elements.size() == 0) {
        root = nullptr;
        return;
    }

    Queue<TreeNode*> q;
    root = new TreeNode(stoi(elements.get(0))); // первый становится корнем
    q.enqueue(root);

    int i = 1;
    while (q.size() > 0 && i < elements.size()) {
        TreeNode* current = q.dequeue();

        if (i < elements.size()) {
            current->left = new TreeNode(stoi(elements.get(i)));
            q.enqueue(current->left);
        }
        i++;

        if (i < elements.size()) {
            current->right = new TreeNode(stoi(elements.get(i)));
            q.enqueue(current->right);
        }
        i++;
    }
}


void CompleteBinaryTree::printNode(TreeNode* node, string prefix, bool isLeft) {
    if (node == nullptr) {
        return;
    }

    cout << prefix; // текущий узел

    if (isLeft) {
        cout << "|-- ";
    } else {
        cout << "\\-- ";
    }

    cout << node->value << endl; // само значение

    string newPrefix = prefix;
    if (isLeft) {
        newPrefix += "|   ";
    } else {
        newPrefix += "   ";
    }
    printNode(node->left, newPrefix, true);
    printNode(node->right, newPrefix, false);
}

void CompleteBinaryTree::printTree() {
    printNode(root, "", false);
}


#endif //LR2_CBT_H
