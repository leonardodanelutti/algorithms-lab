/**
 * Data type for representation of a <b>max tree</b>\n\n\n
 * A <b>max tree</b> T is a binary tree defined recursively in this way:\n\n
 * Given an array A[i..j] and c = (i + j) / 2
 * <ul>
 * <li>T(A[i..j]).value = A[i]                                       if i = j </li>
 * <li>T(A[i..j]).value = max{T(A[i..c]).value, T(A[c+1..j]).value}  if i \< j</li>
 * </ul>
 *
 */
typedef struct node {
    int max;
    struct node *left;
    struct node *right;
} node;

/**
 * Return a node that points to NULL, this represent a leaf of a <b>max tree<b>
 *
 * @param data value of the node
 * @return a new node that represent a leaf
 */
node *new_leaf(int data) {
    node *node = malloc(sizeof(struct node));
    node->max = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * @param a an integer
 * @param b an integer
 * @return max{a, b}
 */
int max_between(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

/**
 * Creates the parent node of a <b>max tree</b> given the two children nodes.\n\n
 * This is done in Θ(1).
 *
 * @param l_node a node struct that represent the left child
 * @param r_node a node struct that represent the right child
 * @return a new node struct that represent the parent node
 */
node *new_node(node *l_node, node *r_node) {
    node *node = malloc(sizeof(struct node));

    int max = max_between(l_node->max, r_node->max);
    node->max = max;
    node->left = l_node;
    node->right = r_node;

    return node;
}

// Global variable, represent the index to be use when creating a leaf
int index_of_leafs;

/**
 * Return a new node struct that represent a <b>max tree</b> from a given array.\n\n
 * This is done in Θ(n).\n\n
 * This function should never be used, use instead <u>new_tree</u>
 *
 * @param a an array of integers
 * @param i a recursion parameter
 * @param j a recursion parameter
 * @return a new node struct that represent the <b>max tree</b>
 */
node *new_tree_rec(int *a, int i, int j) {
    if (i == j) {
        index_of_leafs++;
        return new_leaf(a[index_of_leafs]);

    } else {
        int c = (i + j) / 2;
        node *l_node = new_tree_rec(a, i, c);
        node *r_node = new_tree_rec(a, c + 1, j);
        return new_node(l_node, r_node);
    }
}

/**
 * Return a new node struct that represent a <b>max tree</b> from a given array.\n\n
 * This is done in Θ(n).
 *
 * @param a an array of integers
 * @return a new node struct that represent the <b>max tree</b>
 */
node *new_tree(int *a, int size) {
    index_of_leafs = -1;
    return new_tree_rec(a, 0, size - 1);
}

/**
 * Returns the max value of the leafs of a <b>max tree</b> contained in the range [i..j].\n\n
 * This is done in O(log(n)).\n\n
 * This function should never be used, use instead <u>max</u>
 *
 * @param head a node struct
 * @param n a recursive parameter, left of the current node: head
 * @param m a recursive parameter, right of the current node: head
 * @param i a recursive parameter, left index of the interval in which the maximum is sought
 * @param j a recursive parameter, right index of the interval in which the maximum is sought
 * @return the max value of the leafs contained in [i..j]
 */
int max_rec(node *head, int n, int m, int i, int j) {
    int c = (m + n) / 2;
    if (n == i && m == j) {
        return head->max;
    } else if (i >= n && j <= c) {
        return max_rec(head->left, n, c, i, j);
    } else if (i > c && j <= m) {
        return max_rec(head->right, c + 1, m, i, j);
    } else {
        int a = max_rec(head->left, n, c, i, c);
        int b = max_rec(head->right, c + 1, m, c + 1, j);
        return max_between(a, b);
    }
}

/**
 * Returns the max value of the leafs of a <b>max tree</b> contained in the range [i..j].\n\n
 * This is done in O(log(n)).\n\n
 *
 * @param head a node struct
 * @return the max value of the leafs contained in [i..j]
 */
int max(node *head, int i, int j, int size) {
    return max_rec(head, 0, size - 1, i, j);
}






