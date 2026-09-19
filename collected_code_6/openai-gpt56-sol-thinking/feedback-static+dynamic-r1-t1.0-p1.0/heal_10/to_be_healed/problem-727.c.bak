#include <errno.h>
#include <locale.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_non_alphanumeric(char *text)
{
    regex_t regex;
    regmatch_t match;
    char *read;
    char *write;
    size_t remaining;
    int result;

    if (text == NULL) {
        return EINVAL;
    }

    result = regcomp(&regex, "[^[:alnum:]]+", REG_EXTENDED);
    if (result != 0) {
        return result;
    }

    read = text;
    write = text;
    remaining = strlen(text);

    for (;;) {
        size_t start;
        size_t end;

        result = regexec(&regex, read, 1, &match, 0);

        if (result == REG_NOMATCH) {
            memmove(write, read, remaining + 1);
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

        if (start != 0) {
            memmove(write, read, start);
            write += start;
        }

        read += end;
        remaining -= end;
    }

    regfree(&regex);
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[const])
{
    char *text;
    size_t length;
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

    length = strlen(argv[1]);

    if (length == SIZE_MAX) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    text = malloc(length + 1);
    if (text == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    memcpy(text, argv[1], length + 1);

    result = remove_non_alphanumeric(text);
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