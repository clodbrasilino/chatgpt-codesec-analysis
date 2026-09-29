#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int find_words(const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *pattern = "([[:alnum:]_]{4,})";
    const char *cursor = text;
    int status;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        char message[256];
        regerror(status, &regex, message, sizeof(message));
        fprintf(stderr, "regcomp failed: %s\n", message);
        return EXIT_FAILURE;
    }

    while (*cursor != '\0') {
        status = regexec(&regex, cursor, 1, &match, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            char message[256];
            regerror(status, &regex, message, sizeof(message));
            fprintf(stderr, "regexec failed: %s\n", message);
            regfree(&regex);
            return EXIT_FAILURE;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            fprintf(stderr, "Invalid regular-expression match\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        size_t length = (size_t)(match.rm_eo - match.rm_so);

        if (fwrite(cursor + match.rm_so, 1, length, stdout) != length ||
            fputc('\n', stdout) == EOF) {
            fprintf(stderr, "Failed to write output\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        cursor += match.rm_eo;
    }

    regfree(&regex);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"text\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    return find_words(argv[1]);
}