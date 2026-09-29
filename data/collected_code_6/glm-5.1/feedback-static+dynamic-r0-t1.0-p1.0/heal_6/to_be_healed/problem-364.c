#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int find_min_flips(const char *binary_string, size_t length) {
    if (binary_string == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; i++) {
        if (binary_string[i] != '0' && binary_string[i] != '1') {
            return -1;
        }
    }

    if (length == 0) {
        return 0;
    }

    int flips_starting_with_0 = 0;
    int flips_starting_with_1 = 0;

    for (size_t i = 0; i < length; i++) {
        char expected_0 = (i % 2 == 0) ? '0' : '1';
        char expected_1 = (i % 2 == 0) ? '1' : '0';

        if (binary_string[i] != expected_0) {
            flips_starting_with_0++;
        }
        if (binary_string[i] != expected_1) {
            flips_starting_with_1++;
        }
    }

    return min(flips_starting_with_0, flips_starting_with_1);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);

    char *buffer = malloc(input_len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, input, input_len);
    buffer[input_len] = '\0';

    int result = find_min_flips(buffer, input_len);
    free(buffer);

    if (result == -1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}