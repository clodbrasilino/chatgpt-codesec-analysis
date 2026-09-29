#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_set_bits(unsigned int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

int main(int argc, char const * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned int>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || val > UINT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    unsigned int num = (unsigned int)val;
    int result = count_set_bits(num);

    printf("%d\n", result);
    return EXIT_SUCCESS;
}