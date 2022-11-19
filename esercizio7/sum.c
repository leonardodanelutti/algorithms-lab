/**
 * Returns a new array where each element is the sum of the previous elements in the input array.
 * This array has size n+1, where n is the size of the input.\n\n
 * This is done in Θ(n).
 *
 * @param a an array of integers
 * @param size the size of the array
 * @return a new array with the partial sums of a
 */
int *create_partial_sum(int *a, int size) {
    int *b = malloc((size + 1) * sizeof(int));
    b[0] = 0;
    for (int i = 1; i <= size; i++) {
        b[i] = a[i - 1] + b[i - 1];
    }
    return b;
}

/**
 * Returns the difference of the two elements in an array in position j+1 and i.
 * In other words a[j + 1] - a[i]\n\n
 * This is done in Θ(1).
 *
 * @param a an array of integers
 * @param i a valid index for a, must be ≤ to j
 * @param j a valid index for a, must be ≥ to j
 * @return the difference of the elements in position j+1 and i
 */
int sum(int *a, int i, int j) {
    return a[j + 1] - a[i];
}