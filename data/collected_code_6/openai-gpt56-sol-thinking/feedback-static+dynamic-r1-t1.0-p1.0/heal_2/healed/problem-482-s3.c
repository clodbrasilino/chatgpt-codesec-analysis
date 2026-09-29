#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static void report_regex_error(int error_code, const regex_t *regex)
{
    size_t required_size = regerror(error_code, regex, NULL, 0);
    char *message;

    if (required_size == 0) {
        fprintf(stderr, "Regex error code: %d\n", error_code);
        return;
    }

    message = malloc(required_size);
    if (message == NULL) {
        fprintf(stderr, "Regex error code: %d\n", error_code);
        return;
    }

    regerror(error_code, regex, message, required_size);
    fprintf(stderr, "Regex error: %s\n", message);
    free(message);
}

static int find_sequences(const char *input)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int result;

    if (input == NULL) {
        return -1;
    }

    result = regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED);
    if (result != 0) {
        report_regex_error(result, &regex);
        return -1;
    }

    cursor = input;

    for (;;) {
        size_t match_length;

        result = regexec(&regex, cursor, 1, &match, 0);

        if (result == REG_NOMATCH) {
            break;
        }

        if (result != 0) {
            report_regex_error(result, &regex);
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return -1;
        }

        match_length = (size_t)(match.rm_eo - match.rm_so);

        if (fwrite(cursor + match.rm_so, 1, match_length, stdout) !=
                match_length ||
            fputc('\n', stdout) == EOF) {
            regfree(&regex);
            return -1;
        }

        cursor += match.rm_eo;
    }

    regfree(&regex);
    return 0;
}

int main(int argc, char **const argv)
{
    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s \"string\"\n", program_name);
        return EXIT_FAILURE;
    }

    if (find_sequences(argv[1]) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}