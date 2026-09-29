#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <limits.h>

static int find_words(const char *text)
{
    static const char pattern[] =
        "(^|[^[:alnum:]_])([[:alpha:]]{3,5})($|[^[:alnum:]_])";

    regex_t regex;
    regmatch_t matches[4];
    const char *cursor = text;
    int status = regcomp(&regex, pattern, REG_EXTENDED);

    if (status != 0) {
        size_t size = regerror(status, &regex, NULL, 0);
        char *message = malloc(size);

        if (message != NULL) {
            regerror(status, &regex, message, size);
            fprintf(stderr, "regcomp failed: %s\n", message);
            free(message);
        } else {
            fputs("regcomp failed\n", stderr);
        }

        return EXIT_FAILURE;
    }

    while (*cursor != '\0') {
        status = regexec(&regex, cursor, 4, matches, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            size_t size = regerror(status, &regex, NULL, 0);
            char *message = malloc(size);

            if (message != NULL) {
                regerror(status, &regex, message, size);
                fprintf(stderr, "regexec failed: %s\n", message);
                free(message);
            } else {
                fputs("regexec failed\n", stderr);
            }

            regfree(&regex);
            return EXIT_FAILURE;
        }

        if (matches[2].rm_so < 0 ||
            matches[2].rm_eo < matches[2].rm_so) {
            regfree(&regex);
            return EXIT_FAILURE;
        }

        size_t length =
            (size_t)(matches[2].rm_eo - matches[2].rm_so);

        if (length > (size_t)INT_MAX ||
            printf("%.*s\n", (int)length,
                   cursor + matches[2].rm_so) < 0) {
            regfree(&regex);
            return EXIT_FAILURE;
        }

        if (matches[0].rm_eo <= 0) {
            ++cursor;
        } else {
            cursor += matches[0].rm_eo;
        }
    }

    regfree(&regex);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    const char *program =
        argc > 0 && argv != NULL && argv[0] != NULL
            ? argv[0]
            : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s \"text\"\n", program);
        return EXIT_FAILURE;
    }

    return find_words(argv[1]);
}