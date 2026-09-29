#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static char *remove_present_characters(const char *source,
                                       const char *characters)
{
    unsigned char present[UCHAR_MAX + 1] = {0};
    size_t source_length = 0;
    size_t write_index = 0;
    char *result;

    if (source == NULL || characters == NULL) {
        errno = EINVAL;
        return NULL;
    }

    while (*characters != '\0') {
        present[(unsigned char)*characters] = 1;
        ++characters;
    }

    while (source[source_length] != '\0') {
        if (source_length == SIZE_MAX - 1) {
            errno = EOVERFLOW;
            return NULL;
        }
        ++source_length;
    }

    result = malloc(source_length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t read_index = 0; read_index < source_length; ++read_index) {
        unsigned char current = (unsigned char)source[read_index];

        if (!present[current]) {
            result[write_index++] = source[read_index];
        }
    }

    result[write_index] = '\0';
    return result;
}

static char *read_line(FILE *stream)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer;

    if (stream == NULL) {
        errno = EINVAL;
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return NULL;
            }

            if (length == 0) {
                free(buffer);
                errno = 0;
                return NULL;
            }

            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            errno = EOVERFLOW;
            return NULL;
        }

        if (length + 1 == capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                errno = EOVERFLOW;
                return NULL;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
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
    return buffer;
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

    if (fputs(result, stdout) == EOF ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(result);
    free(second);
    free(first);
    return status;
}