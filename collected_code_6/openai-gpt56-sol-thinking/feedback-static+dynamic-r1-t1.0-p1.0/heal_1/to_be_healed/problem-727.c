#include <errno.h>
#include <locale.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_non_alphanumeric(char *text)
{
    regex_t regex;
    regmatch_t match;
    size_t length;
    int result;

    if (text == NULL) {
        return EINVAL;
    }

    result = regcomp(&regex, "[^[:alnum:]]+", REG_EXTENDED);
    if (result != 0) {
        return result;
    }

    length = strlen(text);

    for (;;) {
        result = regexec(&regex, text, 1, &match, 0);

        if (result == REG_NOMATCH) {
            regfree(&regex);
            return 0;
        }

        if (result != 0) {
            regfree(&regex);
            return result;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so ||
            (size_t)match.rm_eo > length) {
            regfree(&regex);
            return EINVAL;
        }

        {
            size_t start = (size_t)match.rm_so;
            size_t end = (size_t)match.rm_eo;

            memmove(text + start, text + end, length - end + 1);
            length -= end - start;
        }
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *text;
    size_t length;
    int result;
    int status = EXIT_FAILURE;

    if (setlocale(LC_ALL, "") == NULL) {
        if (fputs("Failed to initialize locale.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <text>\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    length = strlen(argv[1]);
    if (length == SIZE_MAX) {
        if (fputs("Input is too large.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    text = malloc(length + 1);
    if (text == NULL) {
        if (fputs("Memory allocation failed.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    memcpy(text, argv[1], length + 1);

    result = remove_non_alphanumeric(text);
    if (result != 0) {
        if (fputs("Failed to process input.\n", stderr) == EOF) {
            free(text);
            return EXIT_FAILURE;
        }
        free(text);
        return EXIT_FAILURE;
    }

    if (puts(text) != EOF) {
        status = EXIT_SUCCESS;
    }

    free(text);
    return status;
}