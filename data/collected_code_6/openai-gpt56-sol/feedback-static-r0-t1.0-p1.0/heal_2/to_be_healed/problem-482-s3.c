#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static void report_regex_error(const char *message, int status, const regex_t *regex)
{
    size_t length = regerror(status, regex, NULL, 0);
    char *buffer;

    if (length == 0) {
        fprintf(stderr, "%s\n", message);
        return;
    }

    buffer = malloc(length);
    if (buffer == NULL) {
        fprintf(stderr, "%s\n", message);
        return;
    }

    regerror(status, regex, buffer, length);
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
        report_regex_error("Regex compilation failed", status, &regex);
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

        if (length > (size_t)INT_MAX ||
            printf("%.*s\n", (int)length, cursor + (size_t)start) < 0) {
            regfree(&regex);
            return -1;
        }

        found = 1;
        cursor += (size_t)end;
    }

    if (status != REG_NOMATCH) {
        report_regex_error("Regex matching failed", status, &regex);
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return found;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"string\"\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    result = find_sequences(argv[1]);
    return result < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}