#include <iostream>
#include <queue>

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

    Node* deleteNode(Node* root, int value) {
        if (!root) return root;
        if (value < root->value)
            root->left = deleteNode(root->left, value);
        else if (value > root->value)
            root->right = deleteNode(root->right, value);
        else {
            if (!root->left) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (!root->right) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            Node* temp = minValueNode(root->right);
            root->value = temp->value;
            root->right = deleteNode(root->right, temp->value);
        }
        return root;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    bool search(Node* root, int value) {
        if (!root) return false;
        if (root->value == value) return true;
        if (value < root->value)
            return search(root->left, value);
        return search(root->right, value);
    }

    void inorder(Node* root) {
        if (root) {
            inorder(root->left);
            std::cout << root->value << " ";
            inorder(root->right);
        }
    }

    void preorder(Node* root) {
        if (root) {
            std::cout << root->value << " ";
            preorder(root->left);
            preorder(root->right);
        }
    }

    void postorder(Node* root) {
        if (root) {
            postorder(root->left);
            postorder(root->right);
            std::cout << root->value << " ";
        }
    }

    void levelOrder(Node* root) {
        if (!root) return;
        std::queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* node = q.front();
            q.pop();
            std::cout << node->value << " ";
            if (node->left != nullptr) q.push(node->left);
            if (node->right != nullptr) q.push(node->right);
        }
    }

public:
    void insert(int value) {
        root = insert(root, value);
    }

    void deleteValue(int value) {
        root = deleteNode(root, value);
    }

    bool search(int value) {
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
