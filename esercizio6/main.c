#include <stdio.h>

#define MAX_LINE_SIZE 10000   // maximum size of a line of input

int scanArray(int *a) {
    // scan line of text
    char line[MAX_LINE_SIZE];
    scanf("%[^\n]", line);

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

int search(int val, int *a, int p, int q){
    int half = (p+q)/2 + 1;
    if (p==q) {
        if (a[p] == val) {
            return p;
        } else {
            return -1;
        }
    } else if (val < a[half]) {
        return search(val, a, p, half-1);
    } else {
        return search(val, a, half, q);
    }
}


int main(){
    int a[MAX_LINE_SIZE];
    int size = scanArray(a);
    int value;
    scanf("%d", &value);
    if (size == 0) {
        printf("-1");
    } else {
        int result = search(value, a, 0, size-1);
        printf("%d", result);
    }
    return 0;
}
