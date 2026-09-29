#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

int count_hexadecimal_numbers(unsigned long long start, unsigned long long end) {
    int count = 0;
    unsigned long long i;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[65];
    /* Possible weaknesses found:
     *  The scope of the variable 'ret' can be reduced. [variableScope]
     */
    int ret;

    if (start > end) {
        return -1;
    }

    for (i = start; i <= end; i++) {
        char *ptr = buffer;
        int valid = 1;

        ret = snprintf(buffer, sizeof(buffer), "%llx", i);
        if (ret < 0 || (size_t)ret >= sizeof(buffer)) {
            return -1;
        }

        while (*ptr != '\0') {
            if (!isxdigit((unsigned char)*ptr)) {
                valid = 0;
                break;
            }
            ptr++;
        }

        if (valid && ptr != buffer) {
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