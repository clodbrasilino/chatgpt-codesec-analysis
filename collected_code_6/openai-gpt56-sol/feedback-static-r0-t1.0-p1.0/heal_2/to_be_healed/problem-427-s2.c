#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int convert_date(const char *input, char *output, size_t output_size)
{
    static const size_t input_length = 10U;
    static const size_t required_size = 11U;
    int written;

    if (input == NULL || output == NULL || output_size < required_size) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(input) != input_length ||
        input[4] != '-' ||
        input[7] != '-') {
        return -1;
    }

    for (size_t i = 0U; i < input_length; ++i) {
        if (i != 4U && i != 7U &&
            (input[i] < '0' || input[i] > '9')) {
            return -1;
        }
    }

    written = snprintf(
        output,
        output_size,
        "%.2s-%.2s-%.4s",
        input + 8,
        input + 5,
        input
    );

    if (written < 0 || (size_t)written >= output_size) {
        return -1;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *converted;
    int status = EXIT_FAILURE;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s yyyy-mm-dd\n", argv[0]);
        return EXIT_FAILURE;
    }

    converted = malloc(11U);
    if (converted == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (convert_date(argv[1], converted, 11U) != 0) {
        fprintf(stderr, "Invalid date format\n");
        goto cleanup;
    }

    if (printf("%s\n", converted) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(converted);
    return status;
}