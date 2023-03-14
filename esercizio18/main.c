#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_LINE_SIZE 10000   // maximum size of a line of input

/// An element of the array, with a value and a null flag
typedef struct {
    int value;
    int null;
} Node;

/// Reads the array from stdin
int scanArray(Node *a) {
    char input[MAX_LINE_SIZE];
    char *token;

    fgets(input, MAX_LINE_SIZE, stdin);

    token = strtok(input, " ");
    int i = 0;
    while (token != NULL) {
        if (strcmp(token, "NULL") == 0 || strcmp(token, "NULL\n") == 0) {
            a[i] = (Node) {0, 1};
        } else {
            a[i] = (Node) {atoi(token), 0};
        }
        token = strtok(NULL, " ");
        i++;
    }
    return i;
}

/**
 * Recursive function to check if the array is a binary search tree
 *
 * @param array the pointer to the array to check
 * @param result the pointer to the result of the check
 * @param pos the position of the current element, recursive parameter
 * @param last the value of the previous element in the recursion, recursive parameter
 * @return the position of the last element of the array
 */
int in_order(Node *array, int *result, int pos, int *last) {
    // The element is null, return the position
    if (array[pos].null)
        return pos;
    // call the function recursively on the left subtree
    int k = in_order(array, result, pos+1, last);
    // check if the current element is greater than the previous one
    *result = *result && *last < array[pos].value;
    // update last
    *last = array[pos].value;
    // call the function recursively on the right subtree
    in_order(array, result, k+1, last);
}

/**
 * Checks if the array is a binary search tree
 *
 * @param array the pointer to the array to check
 * @return 1 if the array is a binary search tree, 0 otherwise
 */
int is_bst(Node *array) {
    int result = 1;
    int last = INT_MIN;
    in_order(array, &result, 0, &last);
    return result;
}

int main() {
    Node *a = calloc(MAX_LINE_SIZE, sizeof(Node));
    int size = scanArray(a);
    a = realloc(a, size*sizeof(Node));
    printf("%d", is_bst(a));
    free(a);
    return 0;
}