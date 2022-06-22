#include <iostream>

class Node {
    public:
        int data;
    Node * left;
    Node * right;
    int height;
};

// Calculate height
int height(Node * node) {
    if (node == NULL)
        return 0;
    return node -> height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// New node creation
Node * newNode(int data) {
    Node * node = new Node();
    node -> data = data;
    node -> left = NULL;
    node -> right = NULL;
    node -> height = 1;
    return (node);
}

// Rotate right
Node * rightRotation(Node * y) {
    Node * x = y -> left;
    Node * z = x -> right;
    x -> right = y;
    y -> left = z;
    y -> height = max(height(y -> left), height(y -> right)) + 1;
    x -> height = max(height(x -> left), height(x -> right)) + 1;
    return x;
}

// Rotate left
Node * leftRotation(Node * x) {
    Node * y = x -> right;
    Node * z = y -> left;
    y -> left = x;
    x -> right = z;
    x -> height = max(height(x -> left), height(x -> right)) + 1;
    y -> height = max(height(y -> left), height(y -> right)) + 1;
    return y;
}

// Get the balance factor of each node
int balanceFactor(Node * node) {
    if (node == NULL)
        return 0;
    return height(node -> left) -
        height(node -> right);
}

// Insert a node
Node * insertNode(Node * node, int data) {
    // Find the correct postion and insert the node
    if (node == NULL)
        return (newNode(data));
    if (data < node -> data)
        node -> left = insertNode(node -> left, data);
    else if (data > node -> data)
        node -> right = insertNode(node -> right, data);
    else
        return node;

    // Update the balance factor of each node and
    // balance the tree
    node -> height = 1 + max(height(node -> left), height(node -> right));
    int balance = balanceFactor(node);
    if (balance > 1) {
        if (data < node -> left -> data) {
            return rightRotation(node);
        } else if (data > node -> left -> data) {
            node -> left = leftRotation(node -> left);
            return rightRotation(node);
        }
    }
    if (balance < -1) {
        if (data > node -> right -> data) {
            return leftRotation(node);
        } else if (data < node -> right -> data) {
            node -> right = rightRotation(node -> right);
            return leftRotation(node);
        }
    }
    return node;
}

void inOrder(Node * root) {
    if (root != NULL) {
        inOrder(root -> left);
        std::cout << root -> data << " ";
        inOrder(root -> right);
    }
}

int main() {
    Node * root = NULL;
    root = insertNode(root, 33); //
    root = insertNode(root, 13); //
    root = insertNode(root, 53); //
    root = insertNode(root, 9); //
    root = insertNode(root, 21); //
    root = insertNode(root, 61); //
    root = insertNode(root, 8); //
    root = insertNode(root, 11); //

    inOrder(root);
    std::cout << std::endl;
}