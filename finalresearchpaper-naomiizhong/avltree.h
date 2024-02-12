#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a node in the AVL tree
typedef struct t_node {
    int key;
    struct t_node* left;
    struct t_node* right;
    int height;
} t_node;

// Function to get the height of a node
int getHeight(t_node* node) {
    if (node == NULL) {
        return 0;
    }
    else {
    return node->height;
    }
}

// Function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new node
t_node* createNode(int key) {
    t_node* newNode = (t_node*)malloc(sizeof(t_node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Function to perform a right rotation
t_node* rightRotate(t_node* a) {
    t_node* b = a->left;
    t_node* c = b->right;

    // Perform rotation
    b->right = a;
    a->left = c;

    // Update heights
    a->height = max(getHeight(a->left), getHeight(a->right)) + 1;
    b->height = max(getHeight(b->left), getHeight(b->right)) + 1;

    return b;
}

// Function to perform a left rotation
t_node* leftRotate(t_node* a) {
    t_node* b = a->right;
    t_node* c = b->left;

    // Perform rotation
    b->left = a;
    a->right = c;

    // Update heights
    a->height = max(getHeight(a->left), getHeight(a->right)) + 1;
    b->height = max(getHeight(b->left), getHeight(b->right)) + 1;

    return b;
}

// Function to get the balance factor of a node
int getBalance(t_node* node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to insert a key into the AVL tree
t_node* insert(t_node* root, int key) {
    
    // Perform standard BST insertion
    if (root == NULL) return createNode(key);

    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    else return root; // Duplicate keys are not allowed

    // Update height of the current node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Get the balance factor to check if this node became unbalanced
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && key < root->left->key) {
        return rightRotate(root);
    }
    // Right Right Case
    if (balance < -1 && key > root->right->key) {
        return leftRotate(root);
    }
    // Left Right Case
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// helper functions to count the number of swaps needed for an avl
//tree to be balanced.
int countSwaps(t_node* root, int key) {
    int swaps = 0;
    t_node* current = root;
    t_node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            swaps++;  // Increment swaps as we pass a node during the search
            current = current->right;
        } else {
            // Duplicate key; no swaps needed
            break;
        }
    }

    return swaps;
}

// Function to find the node with the minimum key value in a given tree
t_node* findMinNode(t_node* node) {
    while (node->left != NULL) node = node->left;
    return node;
}

// Function to delete a key from the AVL tree
t_node* deleteNode(t_node* root, int key) {
    if (root == NULL) return root;

    // Perform standard BST delete
    if (key < root->key) root->left = deleteNode(root->left, key);
    else if (key > root->key) root->right = deleteNode(root->right, key);
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            t_node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            t_node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest
        // in the right subtree)
        t_node* temp = findMinNode(root->right);

        // Copy the inorder successor's content to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }

    // If the tree had only one node, then return
    if (root == NULL) return root;

    // Update height of the current node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Get the balance factor to check if this node became unbalanced
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to perform an in-order traversal and print the elements
void inOrderTraversal(t_node* root) {
    if (root == NULL) return;
    inOrderTraversal(root->left);
    printf("%d ", root->key);
    inOrderTraversal(root->right);
}

// Function to free the memory allocated for the tree
void freeTree(t_node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

/**
 * where node is the root of the avl tree.
*/
t_node* search(t_node* node, int key) {
    if (node == NULL || node->key == key) {
        return node;
    }

    if (node->key > key) {
        
        return search(node->left, key);;
    }
    else {
        return search(node->right, key);
    }
}  
/**    
int main() {
    t_node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("In-order traversal of the AVL tree: ");
    inOrderTraversal(root);
    printf("\n");

    printf("Delete 30 from the AVL tree\n");
    root = deleteNode(root, 30);

    printf("In-order traversal after deletion: ");
    inOrderTraversal(root);
    printf("\n");

    freeTree(root);

    return 0;
}
*/
