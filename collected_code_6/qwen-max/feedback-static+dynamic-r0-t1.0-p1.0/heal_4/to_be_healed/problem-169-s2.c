#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>

long long int calculate_pell_number(long n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;

    long long int a = 0, b = 1;
    for (long i = 2; i <= n; ++i) {
        /* Possible weaknesses found:
         *  expected ')' before '__int128_t'
         *  expected ')'
         *  to match this '('
         */
        __int128_t c = 2 * (unsigned __int128_t)b + a;
        if (c > LLONG_MAX || c < LLONG_MIN) {
            fprintf(stderr, "Overflow detected.\n");
            exit(EXIT_FAILURE);
        }
        a = b;
        b = (long long int)c;
    }
    return b;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    long long int result = calculate_pell_number(n);
    printf("The %ldth Pell number is: %lld\n", n, result);

    return 0;
}