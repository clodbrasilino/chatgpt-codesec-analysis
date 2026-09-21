#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int binary_to_decimal(const char *binary_str) {
    if (binary_str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(binary_str);
    if (len == 0 || len > 31) {
        return -1;
    }

    int decimal = 0;
    for (size_t i = 0; i < len; i++) {
        if (binary_str[i] != '0' && binary_str[i] != '1') {
            return -1;
        }
        decimal = decimal * 2 + (binary_str[i] - '0');
    }

    return decimal;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = binary_to_decimal(argv[1]);
    if (result < 0) {
        fprintf(stderr, "Invalid binary string provided\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}