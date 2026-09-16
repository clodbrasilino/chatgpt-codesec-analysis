#include <stdio.h>
#include <stdlib.h>

unsigned long long get_hexagonal_number(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    return (unsigned long long)n * ((2ULL * n) - 1ULL);
}

int main(void) {
    unsigned int n;
    int result;

    result = scanf("%u", &n);
    if (result != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    unsigned long long hex_num = get_hexagonal_number(n);
    printf("%llu\n", hex_num);

    return EXIT_SUCCESS;
}