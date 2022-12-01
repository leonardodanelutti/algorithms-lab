#include <stdio.h>
#include <limits.h>

int is_bst_rec(int *a, int size, int i, int max, int min) {
    if (i >= size)
        return 1;
    if (a[i] == NULL)
        return 1;
    if (a[i] < min || a[i] > max) {
        return 0;
    }
    return is_bst_rec(a, size, 2*i+1, a[i]-1, min) && is_bst_rec(a, size, 2*i+2, max, a[i]+1);
}

int is_bst(int *a, int size) {
    return is_bst_rec(a, size, 0, INT_MAX, INT_MIN);
}

int main() {
    printf("Hello, World!\n");
    return is_bst();
}
