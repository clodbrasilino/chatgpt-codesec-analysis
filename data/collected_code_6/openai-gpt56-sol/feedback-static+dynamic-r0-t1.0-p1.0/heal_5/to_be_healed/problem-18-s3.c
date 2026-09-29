#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *remove_present_characters(const char *source, const char *characters)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char present[UINT8_MAX + 1] = {0};
    size_t source_length = 0;
    size_t write_index = 0;
    char *result;

    if (source == NULL || characters == NULL) {
        return NULL;
    }

    for (const unsigned char *p = (const unsigned char *)characters;
         *p != '\0';
         ++p) {
        present[*p] = 1;
    }

    for (const char *p = source; *p != '\0'; ++p) {
        if (source_length == SIZE_MAX - 1) {
            return NULL;
        }
        ++source_length;
    }

    result = malloc(source_length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t read_index = 0; read_index < source_length; ++read_index) {
        unsigned char ch = (unsigned char)source[read_index];

        if (present[ch] == 0) {
            result[write_index++] = source[read_index];
        }
    }

    result[write_index] = '\0';
    return result;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 128;
    size_t length = 0;
    char *line = NULL;

    if (stream == NULL) {
        return NULL;
    }

    line = malloc(capacity);
    if (line == NULL) {
        return NULL;
    }

    for (;;) {
        int ch;

        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_line;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return NULL;
            }

            new_capacity = capacity * 2;
            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return NULL;
            }

            line = new_line;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                free(line);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        line[length++] = (char)ch;
    }

    if (length > 0 && line[length - 1] == '\r') {
        --length;
    }

    line[length] = '\0';
    return line;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    char *result = NULL;
    int status = EXIT_FAILURE;

    first = read_line(stdin);
    if (first == NULL) {
        goto cleanup;
    }

    second = read_line(stdin);
    if (second == NULL) {
        goto cleanup;
    }

    result = remove_present_characters(first, second);
    if (result == NULL) {
        goto cleanup;
    }

    if (printf("%s\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(result);
    free(second);
    free(first);
    return status;
}