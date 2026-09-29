#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <locale.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH ((size_t)1024U * 1024U)

int remove_non_alphanumeric(char *text, size_t capacity)
{
    regex_t regex;
    regmatch_t match;
    char *read_position;
    char *write_position;
    size_t length;
    size_t remaining;
    int result;

    if (text == NULL || capacity == 0U) {
        return EINVAL;
    }

    length = strnlen(text, capacity);
    if (length == capacity) {
        return EINVAL;
    }

    result = regcomp(&regex, "[^[:alnum:]]+", REG_EXTENDED);
    if (result != 0) {
        return result;
    }

    read_position = text;
    write_position = text;
    remaining = length;

    for (;;) {
        size_t start;
        size_t end;

        result = regexec(&regex, read_position, 1, &match, 0);

        if (result == REG_NOMATCH) {
            memmove(write_position, read_position, remaining + 1U);
            result = 0;
            break;
        }

        if (result != 0) {
            break;
        }

        if (match.rm_so < 0 ||
            match.rm_eo <= match.rm_so ||
            (uintmax_t)match.rm_eo > (uintmax_t)remaining) {
            result = EINVAL;
            break;
        }

        start = (size_t)match.rm_so;
        end = (size_t)match.rm_eo;

        memmove(write_position, read_position, start);
        write_position += start;
        read_position += end;
        remaining -= end;
    }

    regfree(&regex);
    return result;
}

int main(int argc, char **argv)
{
    const char *input;
    char *text;
    size_t length;
    int result;
    int status;

    if (setlocale(LC_ALL, "") == NULL) {
        fputs("Failed to initialize locale.\n", stderr);
        return EXIT_FAILURE;
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <text>\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return EXIT_FAILURE;
    }

    input = argv[1];
    length = strnlen(input, MAX_INPUT_LENGTH + 1U);

    if (length > MAX_INPUT_LENGTH) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    text = malloc(length + 1U);
    if (text == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    memcpy(text, input, length + 1U);

    result = remove_non_alphanumeric(text, length + 1U);
    if (result != 0) {
        fputs("Failed to process input.\n", stderr);
        free(text);
        return EXIT_FAILURE;
    }

    status = puts(text) == EOF ? EXIT_FAILURE : EXIT_SUCCESS;

    free(text);
    return status;
}