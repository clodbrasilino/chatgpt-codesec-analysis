#include <stdio.h>
#include <stdlib.h>

unsigned long long int nth_decagonal_number(unsigned int n) {
    return (unsigned long long int)n * (4 * n - 3);
}

int main(void) {
    unsigned int n;
    int result;

    result = scanf("%u", &n);

    if (result != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    unsigned long long int decagonal_number = nth_decagonal_number(n);

    printf("%llu\n", decagonal_number);

    return EXIT_SUCCESS;
}