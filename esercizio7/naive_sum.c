
int naive_sum(int *a, int i, int j) {

    int sum = 0;

    for (int n = i; n <= j; n++) {
        sum += a[n];
    }
    return sum;
}
