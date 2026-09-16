#include <stdio.h>
#include <stdlib.h>

unsigned long long count_hex_range(unsigned long long start, unsigned long long end) {
    if (start > end) {
        return 0;
    }
    unsigned long long total_digits = 0;
    for (unsigned long long i = start; i <= end; i++) {
        unsigned long long num = i;
        if (num == 0) {
            total_digits++;
        } else {
            while (num > 0) {
                total_digits++;
                num >>= 4;
            }
        }
    }
    return total_digits;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <start> <end>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr1;
    char *endptr2;
    unsigned long long start = strtoull(argv[1], &endptr1, 10);
    unsigned long long end = strtoull(argv[2], &endptr2, 10);
    if (*endptr1 != '\0' || *endptr2 != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    unsigned long long result = count_hex_range(start, end);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}