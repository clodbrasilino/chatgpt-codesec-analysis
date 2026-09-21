#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fourth_powers_even(uint32_t n, uint64_t *result)
{
    const uint32_t limit = 249U;
    uint64_t sum = 0U;

    if (result == NULL || n > limit) {
        return -1;
    }

    for (uint64_t i = 1U; i <= (uint64_t)n; ++i) {
        uint64_t even = 2U * i;
        uint64_t square = even * even;
        uint64_t fourth = square * square;

        if (sum > UINT64_MAX - fourth) {
            return -1;
        }

        sum += fourth;
    }

    *result = sum;
    return 0;
}

static int discard_line(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch == EOF && ferror(stdin) ? -1 : 0;
}

static int read_line(char **line)
{
    enum { MAX_INPUT_LENGTH = 64 };
    char *buffer;
    size_t length = 0U;
    int ch;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc((size_t)MAX_INPUT_LENGTH + 1U);
    if (buffer == NULL) {
        return -1;
    }

    while (length < (size_t)MAX_INPUT_LENGTH) {
        ch = fgetc(stdin);

        if (ch == '\n') {
            buffer[length] = '\0';
            *line = buffer;
            return 0;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0U) {
                free(buffer);
                return -1;
            }

            buffer[length] = '\0';
            *line = buffer;
            return 0;
        }

        buffer[length++] = (char)ch;
    }

    ch = fgetc(stdin);
    if (ch == '\n') {
        buffer[length] = '\0';
        *line = buffer;
        return 0;
    }

    if (ch == EOF) {
        if (ferror(stdin)) {
            free(buffer);
            return -1;
        }

        buffer[length] = '\0';
        *line = buffer;
        return 0;
    }

    if (discard_line() != 0) {
        free(buffer);
        return -1;
    }

    free(buffer);
    return -1;
}

static int is_space_character(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\r' ||
           ch == '\n' || ch == '\v' || ch == '\f';
}

static int parse_uint32(const char *text, uint32_t *result)
{
    char *end;
    uintmax_t value;

    if (text == NULL || result == NULL) {
        return -1;
    }

    while (is_space_character(*text)) {
        ++text;
    }

    if (*text == '\0' || *text == '-' || *text == '+') {
        return -1;
    }

    errno = 0;
    value = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || value > UINT32_MAX) {
        return -1;
    }

    while (is_space_character(*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *result = (uint32_t)value;
    return 0;
}

int main(void)
{
    char *input = NULL;
    uint32_t value;
    uint64_t sum;

    if (read_line(&input) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (parse_uint32(input, &value) != 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (sum_fourth_powers_even(value, &sum) != 0) {
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}