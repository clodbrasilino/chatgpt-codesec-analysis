#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <stdint.h>

int count_substrings_with_same_ends(const char *str, size_t len, size_t *result)
{
    size_t count;
    size_t i;
    size_t j;

    if (str == NULL || result == NULL) {
        return -1;
    }

    count = 0;

    for (i = 0; i < len; i++) {
        for (j = i; j < len; j++) {
            if (str[i] == str[j]) {
                if (count == SIZE_MAX) {
                    return -2;
                }
                count++;
            }
        }
    }

    *result = count;
    return 0;
}

int main(int argc, const char *argv[])
{
    size_t result;
    int status;
    size_t len;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1] == NULL) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(argv[1]);

    status = count_substrings_with_same_ends(argv[1], len, &result);

    if (status == -1) {
        fprintf(stderr, "Error: Invalid argument passed to function\n");
        return EXIT_FAILURE;
    } else if (status == -2) {
        fprintf(stderr, "Error: Arithmetic overflow detected\n");
        return EXIT_FAILURE;
    } else if (status != 0) {
        fprintf(stderr, "Error: Unknown error occurred\n");
        return EXIT_FAILURE;
    }

    printf("Number of substrings with same first and last characters: %zu\n", result);

    return EXIT_SUCCESS;
}