#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static void report_regex_error(int status, const regex_t *regex, const char *operation)
{
    size_t size = regerror(status, regex, NULL, 0);
    char *message;

    if (size == 0) {
        fprintf(stderr, "%s failed\n", operation);
        return;
    }

    message = malloc(size);
    if (message == NULL) {
        fprintf(stderr, "%s failed; unable to allocate error buffer\n", operation);
        return;
    }

    regerror(status, regex, message, size);
    fprintf(stderr, "%s failed: %s\n", operation, message);
    free(message);
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
        report_regex_error(status, &regex, "regcomp");
        return -1;
    }

    cursor = input;

    for (;;) {
        status = regexec(&regex, cursor, 1, &match, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            report_regex_error(status, &regex, "regexec");
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    const char *program_name = "find_sequences";

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s \"string\"\n", program_name);
        return EXIT_FAILURE;
    }

    if (find_sequences(argv[1]) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}