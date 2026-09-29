#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_hex_numbers(unsigned int start, unsigned int end) {
    if (start > end) {
        return -1;
    }
    if (end == UINT_MAX) {
        return (int)(end - start + 1);
    }
    return (int)((end - start) + 1);
}

int main(int argc, char * const * const argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <start> <end>\n", argv[0]);
        return EXIT_FAILURE;
    }
    unsigned int start = (unsigned int)strtoul(argv[1], NULL, 0);
    unsigned int end = (unsigned int)strtoul(argv[2], NULL, 0);
    int result = count_hex_numbers(start, end);
    if (result < 0) {
        fprintf(stderr, "Invalid range: start must be less than or equal to end\n");
        return EXIT_FAILURE;
    }
    printf("%d\n", result);
    return EXIT_SUCCESS;
}