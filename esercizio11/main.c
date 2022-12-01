#include <stdio.h>
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

int find_candidate(int *a, int size) {
    int candidate = a[0];
    int count = 1;
    for (int i = 1; i < size; i++) {
        if (a[i] == candidate) {
            count++;
        } else if (count != 1) {
            count--;
        } else {
            candidate = a[i];
        }
    }
    return candidate;
}

int test_candidate(int *a, int candidate, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (candidate == a[i]) {
            count++;
        }
    }
    return (count < size/2 + 1) ? 0 : 1;
}


int main() {
    int *a = calloc(MAX_LINE_SIZE, sizeof(int));
    int size = scanArray(a);
    a = realloc(a, size*sizeof(int));

    int candidate = find_candidate(a, size);

    if (test_candidate(a, candidate, size)) {
        printf("%d", candidate);
    } else {
        printf("No majority");
    }

    return 0;
}
