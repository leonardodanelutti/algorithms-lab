int *create_partial_sum(int *a, int size) {
    int *b = malloc((size + 1) * sizeof(int));
    b[0] = 0;
    for (int i = 1; i <= size; i++) {
        b[i] = a[i - 1] + b[i - 1];
    }
    return b;
}

int sum(int *a, int i, int j) {
    return a[j + 1] - a[i];
}