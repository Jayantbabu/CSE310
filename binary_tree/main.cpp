#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct Node {
    int val;
    Node *left, *right;
};

Node *create(int val) {
    Node *temp = new Node;
    temp->val = val;
    temp->left = temp->right = NULL;
    return temp;
}

Node *insert(Node *root, int val) {
    if (root == NULL) {
        return create(val);
    }
    if (val < root->val) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

Node *search(Node *root, int val) {
    if (root == NULL || root->val == val) {
        return root;
    }
    if (val < root->val) {
        return search(root->left, val);
    } else {
        return search(root->right, val);
    }
}

Node *minValueNode(Node *node) {
    Node *current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

Node *deleteNode(Node *root, int val) {
    if (root == NULL) return root;

    if (val < root->val) {
        root->left = deleteNode(root->left, val);
    } else if (val > root->val) {
        root->right = deleteNode(root->right, val);
    } else {
        if (root->left == NULL) {
            Node *temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            delete root;
            return temp;
        }

        Node *temp = minValueNode(root->right);
        root->val = temp->val;
        root->right = deleteNode(root->right, temp->val);
    }
    return root;
}

void inorder(Node *root) {
    if (root == NULL)
        return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

void preorder(Node *root) {
    if (root == NULL)
        return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node *root) {
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";
}

int height(Node *node) {
    if (node == NULL) {
        return 0;
    } else {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
    }
}

void printLevel(Node *root, int level) {
    if (root == NULL) return;
    if (level == 0) {
        cout << root->val << " ";
    } else {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

void levelorder(Node *root) {
    int h = height(root);
    for (int i = 0; i < h; i++) {
        printLevel(root, i);
    }
}

int main() {
    Node* root = NULL;
    int number_of_queries, value;
    string command;
    cin >> number_of_queries;

    for (int i = 0; i < number_of_queries; ++i) {
        cin >> command;
        if (command == "INSERT") {
            cin >> value;
            root = insert(root, value);
        } else if (command == "DELETE") {
            cin >> value;
            root = deleteNode(root, value);
        } else if (command == "SEARCH") {
            cin >> value;
            Node* result = search(root, value);
            cout << (result != NULL ? "True" : "False") << endl;
        } else if (command == "INORDER") {
            inorder(root);
            cout << endl;
        } else if (command == "PREORDER") {
            preorder(root);
            cout << endl;
        } else if (command == "POSTORDER") {
            postorder(root);
            cout << endl;
        } else if (command == "LEVELORDER") {
            levelorder(root);
            cout << endl;
        }
    }

    return 0;
}
