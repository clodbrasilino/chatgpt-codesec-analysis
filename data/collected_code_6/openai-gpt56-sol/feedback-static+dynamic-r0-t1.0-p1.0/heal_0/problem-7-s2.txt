#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int print_long_words(const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int result;

    if (text == NULL) {
        return -1;
    }

    result = regcomp(&regex, "[[:alpha:]]{4,}", REG_EXTENDED);
    if (result != 0) {
        char error_message[256];

        regerror(result, &regex, error_message, sizeof(error_message));
        fprintf(stderr, "regcomp failed: %s\n", error_message);
        return -1;
    }

    cursor = text;

    while ((result = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        size_t length;

        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            regfree(&regex);
            return -1;
        }

        length = (size_t)(match.rm_eo - match.rm_so);

        if (fwrite(cursor + match.rm_so, 1, length, stdout) != length ||
            fputc('\n', stdout) == EOF) {
            regfree(&regex);
            return -1;
        }

        cursor += match.rm_eo;
    }

    if (result != REG_NOMATCH) {
        char error_message[256];

        regerror(result, &regex, error_message, sizeof(error_message));
        fprintf(stderr, "regexec failed: %s\n", error_message);
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *text =
        "This example finds every word containing at least four alphabetic characters.";

    if (print_long_words(text) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}