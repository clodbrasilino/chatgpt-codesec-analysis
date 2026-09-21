#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool meets_requirements(const char *string, size_t required_length)
{
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    size_t length = 0;

    if (string == NULL) {
        return false;
    }

    for (const unsigned char *p = (const unsigned char *)string; *p != '\0'; ++p) {
        ++length;
        has_upper = has_upper || isupper(*p) != 0;
        has_lower = has_lower || islower(*p) != 0;
        has_digit = has_digit || isdigit(*p) != 0;
    }

    return length == required_length && has_upper && has_lower && has_digit;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && ferror(stream)) {
                free(buffer);
                return NULL;
            }

            if (ch == EOF && length == 0) {
                free(buffer);
                return NULL;
            }

            buffer[length] = '\0';
            return buffer;
        }

        if (length == capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                errno = ENOMEM;
                return NULL;
            }

            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }
}

static bool parse_size(const char *text, size_t *value)
{
    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return false;
    }

    errno = 0;
    char *end;
    unsigned long long parsed = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text) {
        return false;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || parsed > SIZE_MAX) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

int main(void)
{
    if (fputs("Enter the required length: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    char *length_line = read_line(stdin);
    if (length_line == NULL) {
        fputs("Invalid length.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t required_length;
    bool valid_length = parse_size(length_line, &required_length);
    free(length_line);

    if (!valid_length) {
        fputs("Invalid length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputs("Enter the string: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    char *input = read_line(stdin);
    if (input == NULL) {
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    bool valid = meets_requirements(input, required_length);
    free(input);

    if (valid) {
        if (fputs("The string meets all requirements.\n", stdout) == EOF) {
            return EXIT_FAILURE;
        }
    } else {
        if (fputs("The string does not meet all requirements.\n", stdout) == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}