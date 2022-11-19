#define N 2147483647

long exponentiation(long base, long exp)
{
    long t = 1L;
    while (exp > 0) {

        // for cases where exponent
        // is not an even value
        if (exp % 2 != 0)
            t = (t * base) % N;

        base = (base * base) % N;
        exp /= 2;
    }
    return t % N;
}

long divide(long x, long y) {
    long inverse = exponentiation(y, N - 2);
    return (inverse * x) % N;
}


typedef struct product_support {
    long *partial_product;
    int *zeros;
} p_support;

p_support *new_p_support(int *a, int size) {

    p_support *supp = malloc(sizeof(p_support));

    long *partial_product = malloc((size + 1) * sizeof(long));
    int *zeros = malloc((size + 1) * sizeof(int));
    partial_product[0] = 1;
    zeros[0] = 0;

    for (int i = 0; i < size; i++) {
        if (a[i] == 0) {
            partial_product[i + 1] = partial_product[i];
            zeros[i + 1] = zeros[i] + 1;
        } else {
            partial_product[i + 1] = (partial_product[i] * (long) a[i]) % N;
            zeros[i + 1] = zeros[i];
        }
    }

    supp->zeros = zeros;
    supp->partial_product = partial_product;

    return supp;
}

long product(p_support *supp, int i, int j) {

    int number_of_zeros = supp->zeros[j + 1] - supp->zeros[i];

    if (number_of_zeros != 0) {
        return 0;
    } else {
        return divide(supp->partial_product[j + 1], supp->partial_product[i]);
    }
}