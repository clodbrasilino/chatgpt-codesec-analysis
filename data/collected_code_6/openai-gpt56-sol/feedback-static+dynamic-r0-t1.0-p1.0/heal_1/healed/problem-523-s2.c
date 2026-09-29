#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool meets_requirements(const char *text, size_t length,
                               size_t required_length)
{
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;

    if (text == NULL || length != required_length) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char c = (unsigned char)text[i];

        has_upper = has_upper || isupper(c) != 0;
        has_lower = has_lower || islower(c) != 0;
        has_digit = has_digit || isdigit(c) != 0;
    }

    return has_upper && has_lower && has_digit;
}

static bool read_size(size_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t count = getline(&line, &capacity, stdin);

    if (count < 0) {
        free(line);
        return false;
    }

    char *end = NULL;
    errno = 0;
    uintmax_t parsed = strtoumax(line, &end, 10);

    while (end != NULL && (*end == ' ' || *end == '\t')) {
        ++end;
    }

    bool valid = errno == 0 &&
                 end != line &&
                 end != NULL &&
                 (*end == '\n' || *end == '\0') &&
                 parsed <= SIZE_MAX;

    if (valid) {
        *value = (size_t)parsed;
    }

    free(line);
    return valid;
}

int main(void)
{
    size_t required_length;

    if (!read_size(&required_length)) {
        return EXIT_FAILURE;
    }

    char *input = NULL;
    size_t capacity = 0;
    ssize_t count = getline(&input, &capacity, stdin);

    if (count < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    size_t length = (size_t)count;

    if (length > 0 && input[length - 1] == '\n') {
        --length;
        if (length > 0 && input[length - 1] == '\r') {
            --length;
        }
    }

    bool valid = meets_requirements(input, length, required_length);
    free(input);

    puts(valid ? "Valid" : "Invalid");
    return EXIT_SUCCESS;
}