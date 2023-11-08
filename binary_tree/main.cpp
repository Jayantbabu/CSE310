#include <iostream>
#include <queue>
#include <stack>

class BinarySearchTree {
private:
    struct Node {
        int value;
        Node *left, *right;

        Node(int val) : value(val), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;

    Node* insert(Node* node, int value) {
        if (!node) return new Node(value);
        if (value < node->value)
            node->left = insert(node->left, value);
        else if (value > node->value)
            node->right = insert(node->right, value);
        return node;
    }

    Node* deleteNode(Node* node, int value) {
        if (!node) return node;

        if (value < node->value) {
            node->left = deleteNode(node->left, value);
        } else if (value > node->value) {
            node->right = deleteNode(node->right, value);
        } else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = minValueNode(node->right);
            node->value = temp->value;
            node->right = deleteNode(node->right, temp->value);
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    bool search(Node* node, int value) const {
        if (!node) return false;
        if (node->value == value) return true;
        else if (value < node->value) return search(node->left, value);
        else return search(node->right, value);
    }

    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            std::cout << node->value << " ";
            inorder(node->right);
        }
    }

    void preorder(Node* node) {
        if (node) {
            postorder(node->right);
            postorder(node->left);
            std::cout << node->value << " ";
        }
    }

    void postorder(Node* node) {
        if (node) {
            std::cout << node->value << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void levelOrder(Node* node) {
        if (!node) return;
        std::queue<Node*> q;
        q.push(node);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            std::cout << current->value << " ";
            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
    }

public:
    void insert(int value) {
        root = insert(root, value);
    }

    void deleteValue(int value) {
        root = deleteNode(root, value);
    }

    bool search(int value) const {
        return search(root, value);
    }

    void inorder() {
        inorder(root);
        std::cout << std::endl;
    }

    void preorder() {
        preorder(root);
        std::cout << std::endl;
    }

    void postorder() {
        postorder(root);
        std::cout << std::endl;
    }

    void levelOrder() {
        levelOrder(root);
        std::cout << std::endl;
    }

    ~BinarySearchTree() {
        clear(root);
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
};

int main() {
    BinarySearchTree bst;
    int queries;
    std::cin >> queries;
    std::string command;
    int value;

    for (int i = 0; i < queries; ++i) {
        std::cin >> command;
        if (command == "INSERT") {
            std::cin >> value;
            bst.insert(value);
        } else if (command == "DELETE") {
            std::cin >> value;
            bst.deleteValue(value);
        } else if (command == "SEARCH") {
            std::cin >> value;
            std::cout << (bst.search(value) ? "True" : "False") << std::endl;
        } else if (command == "INORDER") {
            bst.inorder();
        } else if (command == "PREORDER") {
            bst.preorder();
        } else if (command == "POSTORDER") {
            bst.postorder();
        } else if (command == "LEVELORDER") {
            bst.levelOrder();
        } else {
            std::cout << "Unknown command" << std::endl;
        }
    }

    return 0;
}
