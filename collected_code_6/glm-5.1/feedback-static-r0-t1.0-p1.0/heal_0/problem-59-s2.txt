#include <stdio.h>
#include <stdlib.h>

unsigned long long nth_octagonal_number(unsigned long long n) {
    if (n == 0) {
        return 0;
    }
    if (n > 1844674407370955161ULL) {
        fprintf(stderr, "Overflow\n");
        exit(EXIT_FAILURE);
    }
    return n * (3 * n - 2);
}

int main(void) {
    unsigned long long n;
    if (scanf("%llu", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    unsigned long long result = nth_octagonal_number(n);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}