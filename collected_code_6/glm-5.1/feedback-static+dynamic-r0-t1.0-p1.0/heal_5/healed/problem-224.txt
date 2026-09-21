#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int count_set_bits(unsigned int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0') {
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || val > UINT_MAX) {
        return EXIT_FAILURE;
    }

    unsigned int num = (unsigned int)val;
    int result = count_set_bits(num);

    printf("%d\n", result);
    return EXIT_SUCCESS;
}