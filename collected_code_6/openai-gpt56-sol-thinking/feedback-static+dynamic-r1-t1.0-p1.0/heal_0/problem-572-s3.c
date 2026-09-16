#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define TOKEN_SIZE 128

static int read_token(char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0;
    int too_long = 0;

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return ferror(stdin) ? -1 : 0;
    }

    do {
        if (length + 1 < capacity) {
            buffer[length++] = (char)ch;
        } else {
            too_long = 1;
        }

        ch = fgetc(stdin);
    } while (ch != EOF && !isspace((unsigned char)ch));

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    buffer[length] = '\0';
    return too_long ? -1 : 1;
}

static int read_size(size_t *value)
{
    char token[TOKEN_SIZE];
    char *end;
    uintmax_t parsed;
    int status;

    status = read_token(token, sizeof(token));
    if (status != 1 || token[0] == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' || parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_integer(int *value)
{
    char token[TOKEN_SIZE];
    char *end;
    intmax_t parsed;
    int status;

    status = read_token(token, sizeof(token));
    if (status != 1) {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

static size_t remove_duplicate_numbers(int *values, size_t count)
{
    size_t unique_count = 0;

    for (size_t i = 0; i < count; ++i) {
        size_t j;

        for (j = 0; j < unique_count; ++j) {
            if (values[j] == values[i]) {
                break;
            }
        }

        if (j == unique_count) {
            values[unique_count++] = values[i];
        }
    }

    return unique_count;
}

static int print_list(const int *values, size_t count)
{
    for (size_t i = 0; i < count; ++i) {
        if (i > 0 && fputc(' ', stdout) == EOF) {
            return 0;
        }

        if (fprintf(stdout, "%d", values[i]) < 0) {
            return 0;
        }
    }

    return fputc('\n', stdout) != EOF;
}

int main(void)
{
    size_t list_count;

    if (!read_size(&list_count)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t list_index = 0; list_index < list_count; ++list_index) {
        size_t count;
        size_t unique_count;
        int *values = NULL;

        if (!read_size(&count)) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        if (count > SIZE_MAX / sizeof(*values)) {
            fputs("List is too large\n", stderr);
            return EXIT_FAILURE;
        }

        if (count > 0) {
            values = malloc(count * sizeof(*values));
            if (values == NULL) {
                fputs("Memory allocation failed\n", stderr);
                return EXIT_FAILURE;
            }
        }

        for (size_t i = 0; i < count; ++i) {
            if (!read_integer(&values[i])) {
                free(values);
                fputs("Invalid input\n", stderr);
                return EXIT_FAILURE;
            }
        }

        unique_count = remove_duplicate_numbers(values, count);

        if (!print_list(values, unique_count)) {
            free(values);
            fputs("Output error\n", stderr);
            return EXIT_FAILURE;
        }

        free(values);
    }

    return EXIT_SUCCESS;
}