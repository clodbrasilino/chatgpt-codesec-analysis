#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <locale.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH ((size_t)1024 * 1024)

int remove_non_alphanumeric(char *text, size_t capacity)
{
    regex_t regex;
    regmatch_t match;
    size_t length;
    int result;

    if (text == NULL || capacity == 0) {
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

    for (;;) {
        result = regexec(&regex, text, 1, &match, 0);

        if (result == REG_NOMATCH) {
            result = 0;
            break;
        }

        if (result != 0) {
            break;
        }

        if (match.rm_so < 0 ||
            match.rm_eo <= match.rm_so ||
            (size_t)match.rm_eo > length) {
            result = EINVAL;
            break;
        }

        {
            size_t start = (size_t)match.rm_so;
            size_t end = (size_t)match.rm_eo;
            size_t removed = end - start;

            memmove(text + start, text + end, length - end + 1);
            length -= removed;
        }
    }

    regfree(&regex);
    return result;
}

int main(int argc, char *argv[const])
{
    const char *input;
    char *text;
    size_t length;
    size_t i;
    int result;
    int status = EXIT_FAILURE;

    if (setlocale(LC_ALL, "") == NULL) {
        fputs("Failed to initialize locale.\n", stderr);
        return EXIT_FAILURE;
    }

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <text>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    input = argv[1];
    if (input == NULL) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    length = strnlen(input, MAX_INPUT_LENGTH + 1);
    if (length > MAX_INPUT_LENGTH) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    text = malloc(length + 1);
    if (text == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i <= length; ++i) {
        text[i] = input[i];
    }

    result = remove_non_alphanumeric(text, length + 1);
    if (result != 0) {
        fputs("Failed to process input.\n", stderr);
        free(text);
        return EXIT_FAILURE;
    }

    if (puts(text) != EOF) {
        status = EXIT_SUCCESS;
    }

    free(text);
    return status;
}