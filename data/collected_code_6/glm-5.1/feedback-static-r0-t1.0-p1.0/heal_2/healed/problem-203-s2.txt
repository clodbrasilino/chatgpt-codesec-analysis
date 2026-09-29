#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int hamming_distance(int x, int y) {
    unsigned int xor_val = (unsigned int)x ^ (unsigned int)y;
    int distance = 0;
    while (xor_val) {
        distance += xor_val & 1;
        xor_val >>= 1;
    }
    return distance;
}

int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        size_t len = strlen(argv[0]);
        if (len > 1023) {
            len = 1023;
        }
        char buf[1024];
        memcpy(buf, argv[0], len);
        buf[len] = '\0';
        fprintf(stderr, "Usage: %s <int1> <int2>\n", buf);
        return EXIT_FAILURE;
    }

    char *endptr1, *endptr2;
    errno = 0;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);

    if (errno != 0 || *endptr1 != '\0' || argv[1][0] == '\0' || *endptr2 != '\0' || argv[2][0] == '\0') {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }

    if (val1 < INT_MIN || val1 > INT_MAX || val2 < INT_MIN || val2 > INT_MAX) {
        fprintf(stderr, "Integer overflow\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", hamming_distance((int)val1, (int)val2));

    return EXIT_SUCCESS;
}