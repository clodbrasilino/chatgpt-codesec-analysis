#include <stdio.h>
#include <stdlib.h>

unsigned long long find_nth_rectangular_number(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    return (unsigned long long)n * (n + 1);
}

int main(void) {
    unsigned int n;

    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = find_nth_rectangular_number(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}