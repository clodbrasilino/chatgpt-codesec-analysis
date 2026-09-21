#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static void report_regex_error(int error_code, const regex_t *regex,
                               const char *message)
{
    size_t size;
    char *buffer;

    size = regerror(error_code, regex, NULL, 0);
    if (size == 0) {
        fprintf(stderr, "%s\n", message);
        return;
    }

    buffer = malloc(size);
    if (buffer == NULL) {
        fprintf(stderr, "%s: unable to allocate error buffer\n", message);
        return;
    }

    regerror(error_code, regex, buffer, size);
    fprintf(stderr, "%s: %s\n", message, buffer);
    free(buffer);
}

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
        report_regex_error(result, &regex, "regcomp failed");
        return -1;
    }

    cursor = text;

    for (;;) {
        size_t length;

        result = regexec(&regex, cursor, 1, &match, 0);
        if (result != 0) {
            break;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
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
        report_regex_error(result, &regex, "regexec failed");
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

    return print_long_words(text) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}