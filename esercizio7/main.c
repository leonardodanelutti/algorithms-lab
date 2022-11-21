#include <stdio.h>
#include <stdlib.h>
#include "naive_sum.c"
#include "sum.c"
#include "product.c"
#include "max.c"

#define MAX_LINE_SIZE 10000   // maximum size of a line of input

int scanArray(int *a) {
    // scan line of text
    char line[MAX_LINE_SIZE];
    scanf("%[^\n]", line);
    getchar();

    // convert text into array
    int size = 0, offset = 0, numFilled, n;
    do {
        numFilled = sscanf(line + offset, "%d%n", &(a[size]), &n);
        if (numFilled > 0) {
            size++;
            offset += n;
        }
    } while (numFilled > 0);

    return size;
}

int main() {

    // read first line and place the elements in an array.
    int *a = malloc(MAX_LINE_SIZE * sizeof(int));
    int size_a = scanArray(a);
    if (size_a == 0) {
        printf("-1");
        free(a);
        return 1;
    }
    a = realloc(a, size_a * sizeof(int));

    // read second line and place the elements in an array.
    int *ranges = malloc(MAX_LINE_SIZE * sizeof(int));
    int size_ranges = scanArray(ranges);
    if (size_ranges % 2 == 1 || size_ranges == 0) {
        printf("%d", size_ranges);
        free(ranges);
        return 2;
    }
    ranges = realloc(ranges, size_ranges * sizeof(int));

    // create list of partial sums.
    // int *partial_sum = create_partial_sum(a, size_a);

    // create support struct for finding the product.
    p_support *supp = new_p_support(a, size_a);

    // create support struct for finding the maximum.
    // node *tree = new_tree(a, size_a);

    // loop over ranges array
    for (int i = 0; i < size_ranges; i=i+2) {
        if (ranges[i] > ranges[i+1] || ranges[i] < 0 || ranges[i+1] >= size_a) {
            printf("\nThe %d-th pair does not respect the assumptions.", i/2+1);
            return 3;
        } else {

            // int result = naive_sum(a, ranges[i], ranges[i+1]);

            // return sum between to indices
            // int result = sum(partial_sum, ranges[i], ranges[i+1]);

            // return product between to indices
            int result = product(supp, ranges[i], ranges[i+1]);

            // return maximum between to indices
            // int result = max(tree,ranges[i], ranges[i+1], size_a);

            printf("%d ", result);
        }
    }

    // free(a);
    // free(ranges);
    return 0;
}
