#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int count_hex_numbers(unsigned int start, unsigned int end) {
    if (start > end) {
        return -1;
    }
    if (end == UINT_MAX) {
        if (start == 0) {
            return -1;
        }
        return (int)(end - start + 1);
    }
    unsigned int diff = (end - start) + 1;
    if (diff > (unsigned int)INT_MAX) {
        return -1;
    }
    return (int)diff;
}

int main(int argc, char * const * argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <start> <end>\n", argv[0]);
        return EXIT_FAILURE;
    }
    errno = 0;
    unsigned long start_l = strtoul(argv[1], NULL, 0);
    if (errno != 0 || start_l > UINT_MAX) {
        return EXIT_FAILURE;
    }
    errno = 0;
    unsigned long end_l = strtoul(argv[2], NULL, 0);
    if (errno != 0 || end_l > UINT_MAX) {
        return EXIT_FAILURE;
    }
    unsigned int start = (unsigned int)start_l;
    unsigned int end = (unsigned int)end_l;
    int result = count_hex_numbers(start, end);
    if (result < 0) {
        fprintf(stderr, "Invalid range: start must be less than or equal to end\n");
        return EXIT_FAILURE;
    }
    printf("%d\n", result);
    return EXIT_SUCCESS;
}