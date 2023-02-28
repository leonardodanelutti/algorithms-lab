#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 10000   // maximum size of a line of input

typedef struct {
    int array_len;
    int number_of_nodes;
} Size;

typedef struct {
    int value;
    int null;
} Node;

Size scanArray(Node *a) {

    char input[MAX_LINE_SIZE];
    char *token;

    fgets(input, MAX_LINE_SIZE, stdin);

    token = strtok(input, " ");
    int i = 0;
    int j = 0;
    while (token != NULL) {
        if (strcmp(token, "NULL") == 0 || strcmp(token, "NULL\n") == 0) {
            a[i] = (Node) {0, 1};
        } else {
            a[i] = (Node) {atoi(token), 0};
            j++;
        }
        token = strtok(NULL, " ");
        i++;
    }

    Size size = {i, j};
    return size;
}

int in_order(Node *array, int *result, int pos, int *i) {
    if (array[pos].null)
        return pos+1;
    int k = in_order(array, result, pos+1, i);
    result[*i] = array[pos].value;
    *i = *i + 1;
    in_order(array, result, k, i);
}

int is_sorted(int *array, int size){
    for(int i = 0; i < size-1; i++){
        if(array[i] > array[i+1])
            return 0;
    }
    return 1;
}

int is_bst(Node *array, int size) {
    int *result = calloc(size, sizeof(int));
    int i = 0;
    in_order(array, result, 0, &i);
    int sorted = is_sorted(result, size);
    free(result);
    return sorted;
}


int main() {
    Node *a = calloc(MAX_LINE_SIZE, sizeof(Node));
    Size size = scanArray(a);
    a = realloc(a, size.array_len*sizeof(Node));
    printf("%d", is_bst(a, size.number_of_nodes));
    free(a);
    return 0;
}