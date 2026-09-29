#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096U

static size_t bounded_length(const char *str, size_t max_len)
{
    size_t len = 0U;

    while (len < max_len && str[len] != '\0') {
        len++;
    }

    return len;
}

static char *read_line(FILE *stream)
{
    char *buffer;
    size_t capacity = 128U;
    size_t length = 0U;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (length == 0U) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length >= MAX_INPUT_LEN) {
            continue;
        }

        if (length + 1U >= capacity) {
            char *tmp;
            size_t new_capacity;

            if (capacity > (MAX_INPUT_LEN + 1U) / 2U) {
                new_capacity = MAX_INPUT_LEN + 1U;
            } else {
                new_capacity = capacity * 2U;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return NULL;
            }

            tmp = realloc(buffer, new_capacity);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
            capacity = new_capacity;
        }

        buffer[length] = (char)ch;
        length++;
    }

    while (length > 0U && buffer[length - 1U] == '\r') {
        length--;
    }

    buffer[length] = '\0';

    return buffer;
}

static char *snake_to_camel(const char *input)
{
    char *result;
    size_t len;
    size_t in_pos;
    size_t out_pos;
    int capitalize_next;

    if (input == NULL) {
        return NULL;
    }

    len = bounded_length(input, MAX_INPUT_LEN);

    result = malloc(len + 1U);
    if (result == NULL) {
        return NULL;
    }

    out_pos = 0U;
    capitalize_next = 1;

    for (in_pos = 0U; in_pos < len; in_pos++) {
        unsigned char c = (unsigned char)input[in_pos];

        if (c == (unsigned char)'_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next != 0) {
                result[out_pos] = (char)toupper((int)c);
                capitalize_next = 0;
            } else {
                result[out_pos] = (char)c;
            }
            out_pos++;
        }
    }

    result[out_pos] = '\0';

    return result;
}

int main(void)
{
    int status = EXIT_SUCCESS;
    char *line;

    while ((line = read_line(stdin)) != NULL) {
        char *converted;
        size_t len;

        len = bounded_length(line, MAX_INPUT_LEN);

        if (len == 0U) {
            free(line);
            continue;
        }

        converted = snake_to_camel(line);
        if (converted == NULL) {
            (void)fprintf(stderr, "Conversion failed for: %s\n", line);
            free(line);
            status = EXIT_FAILURE;
            continue;
        }

        free(line);

        if (printf("%s\n", converted) < 0) {
            free(converted);
            status = EXIT_FAILURE;
            break;
        }

        free(converted);

        if (fflush(stdout) != 0) {
            status = EXIT_FAILURE;
            break;
        }
    }

    return status;
}