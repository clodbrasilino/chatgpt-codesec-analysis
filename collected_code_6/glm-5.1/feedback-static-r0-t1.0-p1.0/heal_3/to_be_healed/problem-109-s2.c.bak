#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int count_odd_rotations(const char *str, size_t len) {
    size_t odd_count = 0;
    size_t current_val = 0;

    if (str == NULL || len == 0) {
        return 0;
    }

    if (len > (sizeof(size_t) * CHAR_BIT - 1)) {
        return -1;
    }

    for (size_t i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return -1;
        }
        current_val = (current_val << 1) | (str[i] - '0');
    }

    size_t mask = ((size_t)1 << len) - 1;

    for (size_t i = 0; i < len; i++) {
        if (current_val & 1) {
            odd_count++;
        }
        int msb = (current_val >> (len - 1)) & 1;
        current_val = ((current_val << 1) | msb) & mask;
    }

    if (odd_count > INT_MAX) {
        return -1;
    }

    return (int)odd_count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len = strlen(argv[1]);
    int result = count_odd_rotations(argv[1], len);

    if (result < 0) {
        fprintf(stderr, "Invalid input binary string\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}