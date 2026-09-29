#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_hex_numbers(unsigned long long start, unsigned long long end) {
    int count = 0;
    unsigned long long i = start;

    while (i <= end) {
        if (i > 0) {
            count++;
        }
        if (i == ULLONG_MAX) {
            break;
        }
        i++;
    }

    return count;
}

int main(int argc, char * const argv[]) {
    unsigned long long start = 0;
    unsigned long long end = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <start> <end>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1 = NULL;
    char *endptr2 = NULL;
    
    start = strtoull(argv[1], &endptr1, 10);
    end = strtoull(argv[2], &endptr2, 10);

    if (*endptr1 != '\0' || *endptr2 != '\0') {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    
    if (errno == ERANGE) {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }

    if (start > end) {
        fprintf(stderr, "Start must be less than or equal to end\n");
        return EXIT_FAILURE;
    }

    int result = count_hex_numbers(start, end);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}