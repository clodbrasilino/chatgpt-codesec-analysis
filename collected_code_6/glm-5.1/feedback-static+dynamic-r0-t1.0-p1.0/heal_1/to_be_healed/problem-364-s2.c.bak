#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int count_flips(const char *str) {
    if (str == NULL) {
        return -1;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    for (size_t i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return -1;
        }
    }

    int flips_start_with_0 = 0;
    int flips_start_with_1 = 0;

    for (size_t i = 0; i < len; i++) {
        char expected_0 = (i % 2 == 0) ? '0' : '1';
        char expected_1 = (i % 2 == 0) ? '1' : '0';

        if (str[i] != expected_0) {
            flips_start_with_0++;
        }
        if (str[i] != expected_1) {
            flips_start_with_1++;
        }
    }

    return min(flips_start_with_0, flips_start_with_1);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = count_flips(argv[1]);
    if (result == -1) {
        fprintf(stderr, "Invalid input string\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}