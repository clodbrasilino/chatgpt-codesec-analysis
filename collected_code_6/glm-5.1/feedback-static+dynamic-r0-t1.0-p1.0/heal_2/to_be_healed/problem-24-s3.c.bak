#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

int binary_to_decimal(const char *binary_str, unsigned long long *result) {
    size_t len;
    size_t i;
    unsigned long long decimal_val = 0;

    if (binary_str == NULL || result == NULL) {
        return -1;
    }

    len = strlen(binary_str);
    if (len == 0) {
        return -1;
    }

    for (i = 0; i < len; i++) {
        if (isdigit((unsigned char)binary_str[i]) == 0) {
            return -1;
        }

        if (binary_str[i] != '0' && binary_str[i] != '1') {
            return -1;
        }

        if (decimal_val > ULLONG_MAX / 2) {
            return -1;
        }
        decimal_val <<= 1;

        if (binary_str[i] == '1') {
            if (decimal_val > ULLONG_MAX - 1) {
                return -1;
            }
            decimal_val += 1;
        }
    }

    *result = decimal_val;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    unsigned long long decimal_result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (binary_to_decimal(argv[1], &decimal_result) != 0) {
        fprintf(stderr, "Invalid input or overflow\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", decimal_result);

    return EXIT_SUCCESS;
}