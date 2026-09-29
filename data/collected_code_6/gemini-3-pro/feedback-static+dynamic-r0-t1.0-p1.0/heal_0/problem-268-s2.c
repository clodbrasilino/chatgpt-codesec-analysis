#include <stdio.h>
#include <stdlib.h>

long long int nth_star_number(long long int n) {
    if (n < 1) {
        return 0;
    }
    return 6 * n * (n - 1) + 1;
}

int main(void) {
    long long int n;
    
    if (scanf("%lld", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n < 1) {
        return EXIT_FAILURE;
    }

    long long int result = nth_star_number(n);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}