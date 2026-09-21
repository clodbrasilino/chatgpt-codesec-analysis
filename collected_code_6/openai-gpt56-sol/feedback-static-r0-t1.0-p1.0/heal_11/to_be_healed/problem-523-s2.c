#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
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
        unsigned char ch = (unsigned char)text[i];

        if (isupper(ch) != 0) {
            has_upper = true;
        } else if (islower(ch) != 0) {
            has_lower = true;
        } else if (isdigit(ch) != 0) {
            has_digit = true;
        }
    }

    return has_upper && has_lower && has_digit;
}

static bool discard_line(FILE *stream)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    if (stream == NULL) {
        return false;
    }

    while (fgets(buffer, sizeof buffer, stream) != NULL) {
        size_t i = 0U;

        while (buffer[i] != '\0') {
            if (buffer[i] == '\n') {
                return true;
            }
            ++i;
        }
    }

    return feof(stream) != 0 && ferror(stream) == 0;
}

static bool read_line(FILE *stream, char **line, size_t *length)
{
    size_t capacity = 64U;
    size_t used = 0U;
    char *buffer;

    if (stream == NULL || line == NULL || length == NULL) {
        return false;
    }

    *line = NULL;
    *length = 0U;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        size_t available = capacity - used;

        if (available < 2U) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return false;
            }

            new_capacity = capacity * 2U;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return false;
            }

            buffer = resized;
            capacity = new_capacity;
            available = capacity - used;
        }

        if (fgets(buffer + used, (int)(available > (size_t)INT32_MAX
                                          ? (size_t)INT32_MAX
                                          : available),
                  stream) == NULL) {
            if (ferror(stream) != 0 || used == 0U) {
                free(buffer);
                return false;
            }
            break;
        }

        while (buffer[used] != '\0' && buffer[used] != '\n') {
            ++used;
        }

        if (buffer[used] == '\n') {
            buffer[used] = '\0';
            break;
        }

        if (feof(stream) != 0) {
            break;
        }
    }

    *line = buffer;
    *length = used;
    return true;
}

int main(void)
{
    size_t required_length;
    size_t input_length;
    char *input = NULL;

    if (scanf("%zu", &required_length) != 1) {
        return EXIT_FAILURE;
    }

    if (!discard_line(stdin)) {
        return EXIT_FAILURE;
    }

    if (!read_line(stdin, &input, &input_length)) {
        return EXIT_FAILURE;
    }

    puts(meets_requirements(input, input_length, required_length)
             ? "Valid"
             : "Invalid");

    free(input);
    return EXIT_SUCCESS;
}