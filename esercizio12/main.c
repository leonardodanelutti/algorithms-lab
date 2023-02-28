#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 10000   // maximum size of a line of input

int main() {
    char *s = calloc(MAX_LINE_SIZE, sizeof(char));
    int size;
    int number_of_strings = scanf("%s%n", s, &size);
    if (number_of_strings != 1) {
        printf("Wrong number of arguments.");
        return 1;
    }
    s = realloc(s, size*sizeof(int));

    // b[i] rappresenta la lunghezza massima dei bordi di s[0..i]
    int *b = malloc (size * sizeof(int));
    b[0] = 0;

    // lunghezza del bordo massimo corrente
    int x;

    // aggiorno b[i] in funzione di b[0..i-1]
    for (int i = 1; i<size; i++) {

        // prendo come lunghezza del bordo massimo di s[0..i] la lunghezza del bordo massimo di s[0..i-1]
        x = b[i-1];

        // se il nuovo carattere (del suffisso) non è uguale al carattere successivo al prefisso allora
        while (s[x] != s[i] && x>0) {
            // continuo la comparazione nel successivo bordo massimo
            // che corrisponde al bordo del bordo attuale
            x = b[x-1];
        }
        // se sono uguali aggiungo 1 alla lunghezza del prefisso
        if (s[x] == s[i]) {
            x = x + 1;
        }
        // aggiorno b[i] con l'elemento trovato
        b[i] = x;
    }

    int max_border = b[size-1];
    int min_fractional_period = size-max_border;


    printf("%d", min_fractional_period);

    return 0;
}
