#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *move_numbers_to_end(const char *input)
{
    size_t len;
    size_t i;
    size_t pos;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    result = malloc(len + 1U);
    if (result == NULL) {
        return NULL;
    }

    pos = 0U;
    for (i = 0U; i < len; i++) {
        if (isdigit((unsigned char)input[i]) == 0) {
            result[pos] = input[i];
            pos++;
        }
    }

    for (i = 0U; i < len; i++) {
        if (isdigit((unsigned char)input[i]) != 0) {
            result[pos] = input[i];
            pos++;
        }
    }

    result[pos] = '\0';
    return result;
}

int main(void)
{
    const char *test = "a1b2c3d4";
    char *moved;

    moved = move_numbers_to_end(test);
    if (moved == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }

    if (printf("Original: %s\n", test) < 0) {
        free(moved);
        return EXIT_FAILURE;
    }

    if (printf("Result:   %s\n", moved) < 0) {
        free(moved);
        return EXIT_FAILURE;
    }

    free(moved);
    moved = NULL;

    return EXIT_SUCCESS;
}