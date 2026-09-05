#include <stdio.h>
#include <stdlib.h>

unsigned long long find_nth_bell_number(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }

    unsigned long long *bell = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    if (bell == NULL) {
        exit(EXIT_FAILURE);
    }

    bell[0] = 1;

    for (int i = 1; i <= n; i++) {
        bell[i] = 0;
        for (int j = 0; j < i; j++) {
            /* Possible weaknesses found:
             *  previous implicit declaration of 'binomial' with type 'int()'
             *  implicit declaration of function 'binomial' [-Wimplicit-function-declaration]
             *  previous implicit declaration is here
             *  call to undeclared function 'binomial'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             */
            bell[i] += (bell[j] * (unsigned long long)binomial(i - 1, j));
        }
    }

    unsigned long long result = bell[n];
    free(bell);
    return result;
}

/* Possible weaknesses found:
 *  conflicting types for 'binomial'
 *  conflicting types for 'binomial'; have 'long long unsigned int(int,  int)'
 */
unsigned long long binomial(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    if (k > n - k) {
        k = n - k;
    }
    unsigned long long res = 1;
    for (int i = 0; i < k; i++) {
        res *= (unsigned long long)(n - i);
        res /= (unsigned long long)(i + 1);
    }
    return res;
}

int main(void) {
    int n = 10;
    unsigned long long result = find_nth_bell_number(n);
    printf("%llu\n", result);
    return 0;
}