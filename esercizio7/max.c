typedef struct node {
    int max;
    struct node *left;
    struct node *right;
} node;

node *new_leaf(int data) {
    node *node = malloc(sizeof(struct node));
    node->max = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

int max_between(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

node *new_node(node *l_node, node *r_node) {
    node *node = malloc(sizeof(struct node));

    int max = max_between(l_node->max, r_node->max);
    node->max = max;
    node->left = l_node;
    node->right = r_node;

    return node;
}

int index_of_leafs = -1;

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

node *new_tree(int *a, int size) {
    index_of_leafs = -1;
    return new_tree_rec(a, 0, size - 1);
}

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

int max(node *head, int i, int j, int size) {
    return max_rec(head, 0, size - 1, i, j);
}






