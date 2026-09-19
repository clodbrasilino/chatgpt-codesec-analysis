#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

static int find_words(const char *text)
{
    static const char pattern[] =
        "(^|[^[:alnum:]_])([[:alpha:]]{3,5})($|[^[:alnum:]_])";

    const char *cursor = text;
    regex_t regex;
    regmatch_t matches[4];

    int status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        char message[256];
        regerror(status, &regex, message, sizeof message);
        fprintf(stderr, "regcomp failed: %s\n", message);
        return EXIT_FAILURE;
    }

    while (*cursor != '\0') {
        status = regexec(&regex, cursor, 4, matches, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            char message[256];
            regerror(status, &regex, message, sizeof message);
            fprintf(stderr, "regexec failed: %s\n", message);
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

        if (printf("%.*s\n",
                   (int)length,
                   cursor + matches[2].rm_so) < 0) {
            regfree(&regex);
            return EXIT_FAILURE;
        }

        cursor += matches[2].rm_eo;
    }

    regfree(&regex);
    return EXIT_SUCCESS;
}

int main(int argc, char *const argv[])
{
    if (argc != 2 || argv[1] == NULL) {
        const char *program =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s \"text\"\n", program);
        return EXIT_FAILURE;
    }

    return find_words(argv[1]);
}