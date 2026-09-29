#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static void report_regex_error(int status, const regex_t *regex,
                               const char *message)
{
    size_t size = regerror(status, regex, NULL, 0);
    char *buffer = malloc(size);

    if (buffer == NULL) {
        fprintf(stderr, "%s\n", message);
        return;
    }

    regerror(status, regex, buffer, size);
    fprintf(stderr, "%s: %s\n", message, buffer);
    free(buffer);
}

static int find_sequences(const char *input)
{
    static const char pattern[] = "[[:upper:]][[:lower:]]+";
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int status;

    if (input == NULL) {
        return -1;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        report_regex_error(status, &regex, "regcomp failed");
        regfree(&regex);
        return -1;
    }

    cursor = input;

    for (;;) {
        status = regexec(&regex, cursor, 1, &match, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            report_regex_error(status, &regex, "regexec failed");
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return -1;
        }

        {
            size_t length = (size_t)(match.rm_eo - match.rm_so);

            if (fwrite(cursor + match.rm_so, 1, length, stdout) != length ||
                fputc('\n', stdout) == EOF) {
                regfree(&regex);
                return -1;
            }
        }

        cursor += match.rm_eo;
    }

    regfree(&regex);
    return 0;
}

int main(int argc, char *argv[])
{
    const char *program_name =
        argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s \"string\"\n", program_name);
        return EXIT_FAILURE;
    }

    return find_sequences(argv[1]) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}