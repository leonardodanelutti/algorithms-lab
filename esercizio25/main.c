#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 10000   // maximum size of a line of input

int min(int a, int b, int c) {

    int min;

    if (a < b) {
        min = a;
    } else {
        min = b;
    }
    if (min > c) {
        min = c;
    }

    return min;
}

int editing_distance(const char *s1, const char *s2, int size_str1, int size_str2) {

    int mem[size_str1+1][size_str2+1];
    for (int i = 0; i <= size_str1; i++) {
        for (int j = 0; j <= size_str2; j++) {
            if (i == size_str1) {
                mem[i][j] = size_str2 - j;
            } else if (j == size_str2) {
                mem[i][j] = size_str1 - i;
            } else {
                mem[i][j] = 0;
            }
        }
    }

    for (int i = size_str1-1; i >= 0; i--) {
        for (int j = size_str2-1; j >= 0; j--) {
            if (s1[i] == s2[j]) {
                mem[i][j] = mem[i+1][j+1];
            } else {
                mem[i][j] = 1 + min(mem[i+1][j], mem[i][j+1], mem[i+1][j+1]);
            }
        }
    }

    return mem[0][0];
}


int main() {

    int size_str1, size_str2, mid;

    char *str1 = malloc(MAX_LINE_SIZE * sizeof(char));
    char *str2 = malloc(MAX_LINE_SIZE * sizeof(char));
    scanf("%s%n\n%n%s%n", str1, &size_str1, &mid, str2, &size_str2);
    str1 = realloc(str1, size_str1*sizeof(char));
    str2 = realloc(str2, size_str2*sizeof(char));
    size_str2 = size_str2 - mid;

    int result = editing_distance(str1, str2, size_str1, size_str2);
    printf("%d", result);

    return 0;
}