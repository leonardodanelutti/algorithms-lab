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
        } else if (a[size] == NULL ) {
            size++;
        }
    } while (numFilled != EOF);

    return size;
}

int in_order(int *array, int size, int pos) {
    if (array[pos] == -1)
        return pos+1;
    int k = in_order(array, size, pos+1);
    printf("%d ", array[pos]);
    in_order(array, size, k);
}



int main() {
    int *a = calloc(MAX_LINE_SIZE, sizeof(int));
    int size = scanArray(a);
    a = realloc(a, size*sizeof(int));
    in_order(a, size, 0);
    return 0;
}