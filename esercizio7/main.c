#include <stdio.h>
#include <stdlib.h>
#include "naive_sum.c"
#include "sum.c"
#include "product.c"
#include "max.c"

#define MAX_LINE_SIZE 10000   // maximum size of a line of input

void readline (char *line) {
    int i = 0;
    for(int c = getchar(); c != '\n'; c = getchar()) {
        line[i] = c;
        i++;
    }
}

int scanArray(int *a) {
    // scan line of text
    char line [MAX_LINE_SIZE];
    readline(line);

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
    int *a = malloc(MAX_LINE_SIZE * sizeof(int));
    int size_a = scanArray(a);
    if (size_a == 0) {
        printf("-1");
        free(a);
        return 1;
    }
    realloc(a, size_a * sizeof(int));

    int *ranges = malloc(MAX_LINE_SIZE * sizeof(int));
    int size_ranges = scanArray(ranges);
    if (size_ranges % 2 == 1 || size_ranges == 0) {
        printf("%d", size_ranges);
        free(ranges);
        return 1;
    }
    realloc(ranges, size_ranges * sizeof(int));


    // int *partial_sum = create_partial_sum(a, size_a);

    // p_support *supp = new_p_support(a, size_a);

    node *tree = new_tree(a, size_a);

    printf("%d", size_ranges);
    for (int i = 0; i < size_ranges; i=i+2) {
        printf("%d", i);
        if (ranges[i] > ranges[i+1] || ranges[i] < 0 || ranges[i+1] >= size_a) {
            return 1;
        } else {
            // int result = naive_sum(a, ranges[i], ranges[i+1]);

            // int result = sum(partial_sum, ranges[i], ranges[i+1]);

            // int result = product(supp, ranges[i], ranges[i+1]);

            long result = max(tree,ranges[i], ranges[i+1], size_a);

            printf("%ld ", result);
        }
    }

    free(a);
    free(ranges);
    return 0;
}
