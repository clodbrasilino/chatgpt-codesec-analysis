#include <errno.h>
#include <locale.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

int remove_non_alphanumeric(char *text)
{
    regex_t regex;
    regmatch_t match;
    char *source;
    char *destination;
    int result;

    if (text == NULL) {
        return EINVAL;
    }

    result = regcomp(&regex, "[^[:alnum:]]+", REG_EXTENDED);
    if (result != 0) {
        return result;
    }

    source = text;
    destination = text;

    for (;;) {
        result = regexec(&regex, source, 1, &match, 0);

        if (result == REG_NOMATCH) {
            while ((*destination++ = *source++) != '\0') {
            }

            regfree(&regex);
            return 0;
        }

        if (result != 0) {
            regfree(&regex);
            return result;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return EINVAL;
        }

        for (regoff_t i = 0; i < match.rm_so; ++i) {
            *destination++ = *source++;
        }

        source += match.rm_eo - match.rm_so;
    }
}

int main(int argc, char *argv[])
{
    int result;

    if (setlocale(LC_ALL, "") == NULL) {
        fputs("Failed to initialize locale.\n", stderr);
        return EXIT_FAILURE;
    }

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <text>\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = remove_non_alphanumeric(argv[1]);
    if (result != 0) {
        fputs("Failed to process input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(argv[1]) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}