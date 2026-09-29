#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 0, got 3
  *  test case 2 failed: expected 1, got 2
  */

int count_hexadecimal_numbers(unsigned long long start, unsigned long long end) {
    int count = 0;
    unsigned long long i;
    char buffer[32];

    if (start > end) {
        return -1;
    }

    for (i = start; i <= end; i++) {
        char *ptr;
        int valid;

        snprintf(buffer, sizeof(buffer), "%llx", i);
        ptr = buffer;
        valid = 1;

        while (*ptr != '\0') {
            if (!isxdigit((unsigned char)*ptr)) {
                valid = 0;
                break;
            }
            ptr++;
        }

        if (valid && ptr != buffer) {
            count++;
        }

        if (i == 0xFFFFFFFFFFFFFFFFULL) {
            break;
        }
    }

    return count;
}

int main(void) {
    unsigned long long start, end;
    int result;

    if (scanf("%llu", &start) != 1) {
        fprintf(stderr, "Invalid input for start\n");
        return EXIT_FAILURE;
    }

    if (scanf("%llu", &end) != 1) {
        fprintf(stderr, "Invalid input for end\n");
        return EXIT_FAILURE;
    }

    result = count_hexadecimal_numbers(start, end);

    if (result < 0) {
        fprintf(stderr, "Invalid range: start must be less than or equal to end\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}