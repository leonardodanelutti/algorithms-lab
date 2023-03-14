#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// AVL Tree
typedef struct Node {
    int key;
    char *value;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

/// Max function
int max(int a, int b) {
    return (a > b) ? a : b;
}

/// Return the height of a node
int height(Node *node){
    if (node==NULL)
        return 0;
    return node->height;
}

/// find the node with the minimum key
Node *min_node( Node *node) {

    Node *current = node;

    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

/// Get the balance number of a node
int balance_number(Node *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

/**
 * Right rotation, tree is unbalanced on the left side
 * Return the new root of the tree
 *
 *     node          x
 *     /  \        /  \
 *    x    B  ->  A    node
 *   / \              / \
 *  A  y             y   B
 *
 */
struct Node* right_rot(Node* node){
    Node* x = node->left;
    Node* y = x->right;

    x->right = node;
    node->left = y;

    // update height
    node->height = max(height(node->right), height(node->left)) + 1;
    x->height = max(height(x->right), height(x->left)) + 1;

    return x;
}

/**
 * Left rotation, tree is unbalanced on the right side.
 * Return the new root of the tree
 *
 *   node            x
 *   /  \          /  \
 *  A    x   ->  node  B
 *      / \      / \
 *     y   B    A  y
 *
 */
struct Node* left_rot(Node* node){
    struct Node* x = node->right;
    struct Node* y = x->left;

    x->left = node;
    node->right = y;

    // update height
    node->height = max(height(node->right), height(node->left)) + 1;
    x->height = max(height(x->right), height(x->left)) + 1;

    return x;
}

/**
 * Insert a node in the AVL-tree.
 * Return the new root of the tree
 */
Node *insert(Node *node, int key, char *value) {

    // If the tree is empty, return a new node
    if (node == NULL) {
        struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
        new_node->key   = key;
        new_node->value = value;
        new_node->left   = NULL;
        new_node->right  = NULL;
        new_node->height = 1;
        return new_node;
    }

    // Otherwise, recur down the tree
    if (key < node->key)
        node->left = insert(node->left, key, value);
    else if (key > node->key)
        node->right = insert(node->right, key, value);

    // update height
    node->height = max(height(node->right), height(node->left)) + 1;

    // Balance the tree

    // Get the balance number of the node
    int balance = balance_number(node);

    // left-left case
    if ( balance > 1 && key < node->left->key ) {
        return right_rot(node);
    }

    // left-right case
    if ( balance > 1 && key > node->left->key ) {
        node->left = left_rot(node->left);
        return right_rot(node);
    }

    // right-right case
    if ( balance < -1 && key > node->right->key ) {
        return left_rot(node);
    }

    // right-left case
    if ( balance < -1 && key < node->right->key ) {
        node->right = right_rot(node->right);
        return left_rot(node);
    }

    // return the node
    return node;
}

/**
 * Remove a node from the AVL-tree
 * Return the new root of the tree
 */
Node *remove_node(Node *node, int key) {

    // If the tree is empty, return NULL
    if (node == NULL)
        return node;

    // otherwise, recur down the tree
    if ( key < node->key )
        node->left = remove_node(node->left, key);
    else if ( key > node->key )
        node->right = remove_node(node->right, key);
        // key has been found
    else {
        // node with only one child or no child
        if ((node->left == NULL) || (node->right == NULL)) {

            Node *temp = node->left ? node->left : node->right;

            // no child case
            if (temp == NULL) {
                temp = node;
                node = NULL;
            } else { // one child case
                *node = *temp; // copy the contents of the non-empty child
            }
            free(temp);
            // node with two children
        } else {

            // find successor
            Node* temp = min_node(node->right);

            // copy the successor's data to this node
            node->key = temp->key;
            node->value = temp->value;

            // delete the successor
            node->right = remove_node(node->right, temp->key);
        }
    }

    // If the tree had only one node then return NULL
    if (node == NULL)
        return node;

    // update height
    node->height = 1 + max(height(node->left), height(node->right));

    // balance the tree

    // get the balance number of the node
    int balance = balance_number(node);

    // left-left case
    if (balance > 1 && balance_number(node->left) >= 0)
        return right_rot(node);

    // left-right case
    if (balance > 1 && balance_number(node->left) < 0) {
        node->left = left_rot(node->left);
        return right_rot(node);
    }

    // right-right case
    if (balance < -1 && balance_number(node->right) <= 0)
        return left_rot(node);

    // right-left case
    if (balance < -1 && balance_number(node->right) > 0) {
        node->right = right_rot(node->right);
        return left_rot(node);
    }

    return node;
}

/**
 * Find a node in the tree
 * Return the value of the node
 */
char *find(Node *root, int key) {
    if (root == NULL) {
        return NULL;
    } else if (key < root->key) {
        find(root->left, key);
    } else if (key > root->key) {
        find(root->right, key);
    } else {
        return root->value;
    }
}

/// Clear the tree
void clear(Node *tree) {
    if (tree == NULL) {
        return;
    }
    clear(tree->left);
    clear(tree->right);
    free(tree);
}

/// Print the tree in polish notation
void show(Node *node) {
    if (node == NULL) {
        printf("NULL ");
        return;
    }

    printf("%d:%s:%d ", node->key, node->value, node->height);

    show(node->left);
    show(node->right);
}

int main() {

    int key;
    char *value = (char *) malloc(200 * sizeof(char));
    char instruction[10];
    Node *tree = NULL;

    // read the instructions
    while (scanf("%s", instruction) != EOF) {
        if (strcmp(instruction, "insert") == 0) {
            scanf("%d %s", &key, value);
            tree = insert(tree, key, value);
            value = (char *) malloc(200 * sizeof(char));
        } else if (strcmp(instruction, "find") == 0) {
            scanf("%d", &key);
            printf("%s", find(tree, key));
        } else if (strcmp(instruction, "remove") == 0) {
            scanf("%d", &key);
            tree = remove_node(tree, key);
        } else if (strcmp(instruction, "clear") == 0) {
            clear(tree);
        } else if (strcmp(instruction, "show") == 0) {
            show(tree);
        } else {
            return 0;
        }
    }

    return 0;
}
