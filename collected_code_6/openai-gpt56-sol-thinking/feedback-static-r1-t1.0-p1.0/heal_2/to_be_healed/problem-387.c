#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(FILE *stream, char **line)
{
    size_t capacity = 256;
    size_t length = 0;
    char *buffer;
    int ch;

    if (stream == NULL || line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
        char *new_buffer;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (ch == '\0') {
            free(buffer);
            return 0;
        }

        if (length == capacity - 1) {
            if (capacity > (size_t)-1 / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF) {
        if (ferror(stream) || length == 0) {
            free(buffer);
            return 0;
        }
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int hex_is_even(const char *input, bool *is_even)
{
    const unsigned char *p;
    unsigned int last_digit = 0;
    size_t digit_count = 0;

    if (input == NULL || is_even == NULL) {
        return 0;
    }

    p = (const unsigned char *)input;

    while (isspace(*p)) {
        ++p;
    }

    if (*p == '+') {
        ++p;
    } else if (*p == '-') {
        return 0;
    }

    if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
        p += 2;
    }

    while (isxdigit(*p)) {
        if (*p >= '0' && *p <= '9') {
            last_digit = (unsigned int)(*p - '0');
        } else {
            last_digit = (unsigned int)(tolower(*p) - 'a' + 10);
        }

        ++digit_count;
        ++p;
    }

    while (isspace(*p)) {
        ++p;
    }

    if (digit_count == 0 || *p != '\0') {
        return 0;
    }

    *is_even = (last_digit % 2U) == 0U;
    return 1;
}

int main(void)
{
    char *input;
    bool is_even;
    int result;

    if (!read_line(stdin, &input)) {
        return EXIT_FAILURE;
    }

    result = hex_is_even(input, &is_even);
    free(input);

    if (!result) {
        return EXIT_FAILURE;
    }

    if (puts(is_even ? "Even" : "Odd") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}