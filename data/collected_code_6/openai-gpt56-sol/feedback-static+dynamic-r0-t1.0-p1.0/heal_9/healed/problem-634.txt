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

    for (uint64_t i = 1U; i <= n; ++i) {
        const uint64_t even = 2U * i;
        const uint64_t square = even * even;
        const uint64_t fourth = square * square;

        if (sum > UINT64_MAX - fourth) {
            return -1;
        }

        sum += fourth;
    }

    *result = sum;
    return 0;
}

static int read_line(char **line)
{
    enum { MAX_INPUT_LENGTH = 64 };
    size_t capacity = 16U;
    size_t length = 0U;
    char *buffer;
    int ch;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;

        if (length >= MAX_INPUT_LENGTH) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }

            free(buffer);
            return -1;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity = capacity * 2U;

            if (new_capacity > MAX_INPUT_LENGTH + 1U) {
                new_capacity = MAX_INPUT_LENGTH + 1U;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0U)) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
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
    end = NULL;
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