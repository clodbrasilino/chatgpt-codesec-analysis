#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_odd_squares(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;
    uint64_t c;

    if (result == NULL || n > UINT64_C(3024616)) {
        return 0;
    }

    a = n;
    b = UINT64_C(2) * n - UINT64_C(1);
    c = UINT64_C(2) * n + UINT64_C(1);

    if (a % UINT64_C(3) == 0) {
        a /= UINT64_C(3);
    } else if (b % UINT64_C(3) == 0) {
        b /= UINT64_C(3);
    } else {
        c /= UINT64_C(3);
    }

    *result = a * b * c;
    return 1;
}

static int read_line(char **buffer)
{
    char *line;
    size_t capacity = 64;
    size_t length = 0;

    if (buffer == NULL) {
        return 0;
    }

    *buffer = NULL;
    line = malloc(capacity);
    if (line == NULL) {
        return 0;
    }

    for (;;) {
        int ch;

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return 0;
            }

            new_capacity = capacity * 2;
            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return 0;
            }

            line = new_line;
            capacity = new_capacity;
        }

        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(line);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        line[length++] = (char)ch;
    }

    line[length] = '\0';
    *buffer = line;
    return 1;
}

static int is_space_character(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

int main(void)
{
    char *buffer = NULL;
    char *first;
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (!read_line(&buffer)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    first = buffer;
    while (is_space_character(*first)) {
        ++first;
    }

    if (*first == '\0' || *first == '-' || *first == '+') {
        free(buffer);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(first, &end, 10);

    if (errno == ERANGE || end == first || input > UINT64_MAX) {
        free(buffer);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (is_space_character(*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(buffer);

    if (!sum_of_odd_squares((uint64_t)input, &result)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}