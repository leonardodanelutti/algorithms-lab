#include <stdio.h>

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

typedef struct {
    int i,j;
} int_pair;

int_pair cerca_somma(int *v, int n, int s){
    for (int i = 0, j = n-1; i < j;) {
        if (v[i] + v[j] == s)
            return (int_pair) {i, j};
        else if ((v[i] + v[j]) < s)
            i++;
        else
            j--;
    }
    return (int_pair) {-1, -1};
}

int main() {
    int a[10000];
    int n = scanArray(a);
    int s;
    scanf("%d", &s);
    int_pair p = cerca_somma(a, n, s);
    printf("%d %d", p.i, p.j);
    return 0;
}
