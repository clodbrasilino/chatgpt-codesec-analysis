#include <stdio.h>
#include <stdlib.h>

int is_polite(unsigned int n) {
    return (n & (n + 1)) != 0;
}

unsigned int nth_polite(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    unsigned int count = 0;
    unsigned int num = 1;
    while (count < n) {
        if (is_polite(num)) {
            count++;
        }
        num++;
    }
    return num - 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long n = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || n <= 0) {
        fprintf(stderr, "Invalid input: %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    printf("%u\n", nth_polite((unsigned int)n));
    return EXIT_SUCCESS;
}