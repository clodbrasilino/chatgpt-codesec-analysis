#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_sum_first_n_odds(uint64_t n, uint64_t *result)
{
    uint64_t n_squared;

    if (result == NULL || n > UINT64_C(77935)) {
        return 0;
    }

    n_squared = n * n;
    *result = n_squared * (UINT64_C(2) * n_squared - UINT64_C(1));

    return 1;
}

static int read_input(char **buffer)
{
    size_t capacity = 32;
    size_t length = 0;
    int ch;
    char *input;

    if (buffer == NULL) {
        return 0;
    }

    input = malloc(capacity);
    if (input == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *new_input;

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(input);
                return 0;
            }

            new_capacity = capacity * 2;
            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return 0;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return 0;
    }

    input[length] = '\0';
    *buffer = input;

    return 1;
}

int main(void)
{
    char *input = NULL;
    char *end;
    uintmax_t value;
    uint64_t result;
    int status = EXIT_FAILURE;

    if (!read_input(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    if (!cube_sum_first_n_odds((uint64_t)value, &result)) {
        fputs("Input is too large\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}