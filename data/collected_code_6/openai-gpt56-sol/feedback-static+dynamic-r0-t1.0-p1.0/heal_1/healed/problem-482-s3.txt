#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static void report_regex_error(int status, const regex_t *regex, const char *message)
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
    static const char pattern[] =
        "(^|[^[:alpha:]])([[:upper:]][[:lower:]]+)";
    regex_t regex;
    regmatch_t matches[3];
    const char *cursor = input;
    int status;
    int found = 0;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        report_regex_error(status, &regex, "Regex compilation failed");
        return -1;
    }

    while ((status = regexec(&regex, cursor, 3, matches, 0)) == 0) {
        regoff_t start = matches[2].rm_so;
        regoff_t end = matches[2].rm_eo;
        size_t length;

        if (start < 0 || end < start) {
            regfree(&regex);
            return -1;
        }

        length = (size_t)(end - start);

        if (length > 0 &&
            fwrite(cursor + (size_t)start, 1, length, stdout) != length) {
            regfree(&regex);
            return -1;
        }

        if (fputc('\n', stdout) == EOF) {
            regfree(&regex);
            return -1;
        }

        found = 1;
        cursor += (size_t)end;
    }

    if (status != REG_NOMATCH) {
        report_regex_error(status, &regex, "Regex matching failed");
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return found;
}

int main(int argc, char *argv[])
{
    int result;

    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s \"string\"\n", program);
        return EXIT_FAILURE;
    }

    result = find_sequences(argv[1]);
    return result < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}