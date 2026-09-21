#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int read_line(FILE *stream, char **line)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;

    if (stream == NULL || line == NULL) {
        return 0;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
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

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int find_substrings(const char *text, const char *substring,
                           size_t **positions, size_t *count)
{
    size_t capacity = 0;
    size_t used = 0;
    size_t *result = NULL;
    size_t text_length;
    size_t substring_length;
    size_t offset;

    if (text == NULL || substring == NULL ||
        positions == NULL || count == NULL) {
        return 0;
    }

    *positions = NULL;
    *count = 0;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    text_length = strlen(text);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    substring_length = strlen(substring);

    if (substring_length == 0 || substring_length > text_length) {
        return 1;
    }

    for (offset = 0; offset <= text_length - substring_length; ++offset) {
        if (memcmp(text + offset, substring, substring_length) == 0) {
            if (used == capacity) {
                size_t new_capacity;
                size_t *new_result;

                if (capacity == 0) {
                    new_capacity = 8;
                } else {
                    if (capacity > SIZE_MAX / 2) {
                        free(result);
                        return 0;
                    }
                    new_capacity = capacity * 2;
                }

                if (new_capacity > SIZE_MAX / sizeof(*result)) {
                    free(result);
                    return 0;
                }

                new_result = realloc(result,
                                     new_capacity * sizeof(*new_result));
                if (new_result == NULL) {
                    free(result);
                    return 0;
                }

                result = new_result;
                capacity = new_capacity;
            }

            result[used++] = offset;
        }
    }

    *positions = result;
    *count = used;
    return 1;
}

int main(void)
{
    char *text = NULL;
    char *substring = NULL;
    size_t *positions = NULL;
    size_t count = 0;
    size_t i;
    int status = EXIT_FAILURE;

    if (!read_line(stdin, &text) || !read_line(stdin, &substring)) {
        goto cleanup;
    }

    if (substring[0] == '\0') {
        goto cleanup;
    }

    if (!find_substrings(text, substring, &positions, &count)) {
        goto cleanup;
    }

    if (printf("Occurrences: %zu\n", count) < 0) {
        goto cleanup;
    }

    for (i = 0; i < count; ++i) {
        if (printf("Position: %zu\n", positions[i]) < 0) {
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(positions);
    free(substring);
    free(text);
    return status;
}