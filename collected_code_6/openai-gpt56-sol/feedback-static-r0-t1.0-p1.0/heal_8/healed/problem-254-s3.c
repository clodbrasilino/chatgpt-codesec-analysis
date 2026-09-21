#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int print_matching_words(const char *text)
{
    const unsigned char *p;

    if (text == NULL) {
        return -1;
    }

    p = (const unsigned char *)text;

    while (*p != '\0') {
        const unsigned char *start;
        size_t length;
        int first;

        while (*p != '\0' && !isalpha(*p)) {
            ++p;
        }

        if (*p == '\0') {
            break;
        }

        start = p;

        while (*p != '\0' && isalpha(*p)) {
            ++p;
        }

        length = (size_t)(p - start);
        first = tolower(start[0]);

        if (first == 'a' || first == 'e') {
            if (fwrite(start, 1U, length, stdout) != length ||
                fputc('\n', stdout) == EOF) {
                return -1;
            }
        }
    }

    return 0;
}

static int read_line(FILE *stream, char **buffer)
{
    char *line;
    size_t capacity = 128U;
    size_t length = 0U;

    if (stream == NULL || buffer == NULL) {
        return -1;
    }

    *buffer = NULL;
    line = malloc(capacity);

    if (line == NULL) {
        return -1;
    }

    for (;;) {
        int ch;

        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(line);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\0') {
            free(line);
            return -1;
        }

        if (length >= capacity - 1U) {
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2U) {
                free(line);
                return -1;
            }

            new_capacity = capacity * 2U;
            temporary = realloc(line, new_capacity);

            if (temporary == NULL) {
                free(line);
                return -1;
            }

            line = temporary;
            capacity = new_capacity;
        }

        line[length++] = (char)(unsigned char)ch;
    }

    line[length] = '\0';
    *buffer = line;
    return 0;
}

int main(void)
{
    char *line = NULL;
    int status = EXIT_FAILURE;

    if (read_line(stdin, &line) != 0) {
        goto cleanup;
    }

    if (print_matching_words(line) != 0) {
        goto cleanup;
    }

    if (fflush(stdout) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(line);
    return status;
}