#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <limits.h>

static int report_regex_error(int status, const regex_t *regex, const char *operation)
{
    size_t size = regerror(status, regex, NULL, 0);
    char *message = malloc(size);

    if (message == NULL) {
        fprintf(stderr, "%s failed\n", operation);
        return EXIT_FAILURE;
    }

    regerror(status, regex, message, size);
    fprintf(stderr, "%s failed: %s\n", operation, message);
    free(message);

    return EXIT_FAILURE;
}

static int find_words(const char *text)
{
    static const char pattern[] =
        "(^|[^[:alnum:]_])([[:alpha:]]{3,5})($|[^[:alnum:]_])";
    const char *cursor = text;
    regex_t regex;
    regmatch_t matches[4];

    int status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return report_regex_error(status, &regex, "regcomp");
    }

    while (*cursor != '\0') {
        status = regexec(&regex, cursor, 4, matches, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            report_regex_error(status, &regex, "regexec");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        if (matches[2].rm_so < 0 ||
            matches[2].rm_eo < matches[2].rm_so ||
            matches[2].rm_eo > INT_MAX) {
            regfree(&regex);
            return EXIT_FAILURE;
        }

        size_t length = (size_t)(matches[2].rm_eo - matches[2].rm_so);

        if (length > (size_t)INT_MAX ||
            printf("%.*s\n", (int)length,
                   cursor + (size_t)matches[2].rm_so) < 0) {
            regfree(&regex);
            return EXIT_FAILURE;
        }

        if (matches[2].rm_eo == 0) {
            ++cursor;
        } else {
            cursor += (size_t)matches[2].rm_eo;
        }
    }

    regfree(&regex);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    if (argc != 2 || argv[1] == NULL) {
        const char *program =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s \"text\"\n", program);
        return EXIT_FAILURE;
    }

    return find_words(argv[1]);
}