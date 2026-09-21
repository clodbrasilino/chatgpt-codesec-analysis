#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

int count_hexadecimal_numbers(unsigned long long start, unsigned long long end) {
    int count = 0;
    unsigned long long i;
    char buffer[65];
    char *endptr;

    if (start > end) {
        return -1;
    }

    for (i = start; i <= end; i++) {
        int valid = 1;
        int ret;

        ret = snprintf(buffer, sizeof(buffer), "%llx", i);
        if (ret < 0 || (size_t)ret >= sizeof(buffer)) {
            return -1;
        }

        endptr = buffer;
        while (*endptr != '\0') {
            if (!isxdigit((unsigned char)*endptr)) {
                valid = 0;
                break;
            }
            endptr++;
        }

        if (valid && endptr != buffer) {
            if (count == INT_MAX) {
                return -1;
            }
            count++;
        }

        if (i == ULLONG_MAX) {
            break;
        }
    }

    return count;
}

int main(void) {
    unsigned long long start, end;
    int result;

    printf("Enter start of range (decimal): ");
    if (scanf("%llu", &start) != 1) {
        fprintf(stderr, "Invalid input for start\n");
        return EXIT_FAILURE;
    }

    printf("Enter end of range (decimal): ");
    if (scanf("%llu", &end) != 1) {
        fprintf(stderr, "Invalid input for end\n");
        return EXIT_FAILURE;
    }

    result = count_hexadecimal_numbers(start, end);

    if (result < 0) {
        fprintf(stderr, "Invalid range: start must be less than or equal to end\n");
        return EXIT_FAILURE;
    }

    printf("Count of hexadecimal numbers in range: %d\n", result);

    return EXIT_SUCCESS;
}