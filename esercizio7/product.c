//! N is the highest prime writable in sizeof(int) bytes
//! MUST BE sizeof(long long) >= 2 * sizeof(int)
#define N 2147483647

/**
 * Returns the result of the exponentiation modulo N.\n\n
 * This is done in Θ(log(exp)).
 *
 * @param base an integer
 * @param exp an integer
 * @return base^(exp) % N
 */
long exponentiation(int base, int exp) {
    long long t = 1L;
    while (exp > 0) {

        if (exp % 2 == 1)
            t = (t * base) % N;

        base = ((long long) base * base) % N;
        exp /= 2;
    }
    return (int) t;
}

/**
 * Returns the result of the division of two numbers modulo N.\n\n
 * This is done in Θ(1).
 *
 * @param x an integer, the divider
 * @param y an integer, the divisor
 * @return (x / y) % N
 */
int division(int x, int y) {
    int inverse = exponentiation(y, N - 2);
    return (int) (((long long)inverse * x) % N);
}

/**
 * Data type for representation of a <b>product support</b>.\n\n\n
 * A <b>product support</b> has two fields:
 * <ul>
 * <li><u>partial_product</u>: partial product of an array modulo N</li>
 * <li><u>zero</u>: partial sum of zeros in an array</li>
 * </ul>
 */
typedef struct product_support {
    int *partial_product;
    int *zeros;
} p_support;

/**
 * Creates a new <b>product support</b> given an array and his size(n).\n\n
 * This is done in Θ(n).
 *
 * @param a an array of integers
 * @param size the size of the array
 * @return a new product support struct of a
 */
p_support *new_p_support(const int *a, int size) {

    p_support *supp = malloc(sizeof(p_support));

    int *partial_product = malloc((size + 1) * sizeof(long));
    int *zeros = malloc((size + 1) * sizeof(int));
    partial_product[0] = 1;
    zeros[0] = 0;

    for (int i = 0; i < size; i++) {
        if (a[i] == 0) {
            partial_product[i + 1] = partial_product[i];
            zeros[i + 1] = zeros[i] + 1;
        } else {
            partial_product[i + 1] = (int) (((long long) partial_product[i] * a[i]) % N);
            zeros[i + 1] = zeros[i];
        }
    }

    supp->zeros = zeros;
    supp->partial_product = partial_product;

    return supp;
}

/**
 * Returns the quotient modulo N of the two elements in an array in position j+1 and i.
 * In other words (a[j + 1] / a[i]) % N\n\n
 * This is done in Θ(1).
 *
 * @param a an array of integers
 * @param i a valid index for a, must be ≤ to j
 * @param j a valid index for a, must be ≥ to j
 * @return the quotient of the elements in position j+1 and i
 */
long product(p_support *supp, int i, int j) {

    int number_of_zeros = supp->zeros[j + 1] - supp->zeros[i];

    if (number_of_zeros != 0) {
        return 0;
    } else {
        return division(supp->partial_product[j + 1], supp->partial_product[i]);
    }
}