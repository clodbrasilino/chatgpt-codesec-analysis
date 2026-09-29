#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_sum_first_n_odds(uint64_t n, uint64_t *result)
{
    uint64_t square;

    if (result == NULL || n > UINT64_C(55108)) {
        return 0;
    }

    square = n * n;
    *result = square * (UINT64_C(2) * square - UINT64_C(1));
    return 1;
}

static int read_input(char **buffer)
{
    size_t capacity = 64;
    size_t length = 0;
    char *input;

    if (buffer == NULL) {
        return 0;
    }

    *buffer = NULL;
    input = malloc(capacity);
    if (input == NULL) {
        return 0;
    }

    for (;;) {
        int ch;

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(input);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return 0;
            }

            input = resized;
            capacity = new_capacity;
        }

        ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(input);
                return 0;
            }
            break;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    input[length] = '\0';
    *buffer = input;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;
    uintmax_t value;
    uint64_t result;

    if (!read_input(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || value > UINT64_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!cube_sum_first_n_odds((uint64_t)value, &result)) {
        free(input);
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}