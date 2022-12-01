#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

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

    int *a = calloc(MAX_LINE_SIZE, sizeof(int));
    int size = scanArray(a);
    a = realloc(a, size*sizeof(int));

    int partial_min = INT_MAX;
    int max = INT_MIN;
    int pos_partial_min = -1;
    int pos_i = -1;
    int pos_j = -1;
    for (int i = 0; i < size; i++) {
        if (a[i] < partial_min) {
            partial_min = a[i];
            pos_partial_min = i;
        }
        if (a[i] - partial_min > max) {
            max = a[i] - partial_min;
            pos_i = pos_partial_min;
            pos_j = i;
        }
    }
    printf("%d %d", pos_i, pos_j);
    return 0;
}
