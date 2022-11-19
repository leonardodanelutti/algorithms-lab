/**
 * Returns the sum of the elements in an array between to indices 0 ≤ i ≤ j ≤ n, where n is the array size.\n
 * This is done in O(n).
 *
 * @param a an array of integers
 * @param i a valid index for a, must be ≤ to j
 * @param j a valid index for a, must be ≥ to j
 * @return the sum of the elements between the indices in the array
 */
int naive_sum(int *a, int i, int j) {
    int sum = 0;
    for (int n = i; n <= j; n++) {
        sum += a[n];
    }
    return sum;
}
