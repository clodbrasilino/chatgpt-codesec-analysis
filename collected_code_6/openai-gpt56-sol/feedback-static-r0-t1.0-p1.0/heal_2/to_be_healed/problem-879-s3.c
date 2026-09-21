#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int matches_pattern(const char *input, bool *matches)
{
    regex_t regex;
    int result;

    if (input == NULL || matches == NULL) {
        return REG_BADPAT;
    }

    *matches = false;

    result = regcomp(&regex, "^a.*b$", REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return result;
    }

    result = regexec(&regex, input, 0, NULL, 0);
    if (result == 0) {
        *matches = true;
        result = 0;
    } else if (result == REG_NOMATCH) {
        result = 0;
    }

    regfree(&regex);
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    bool matches;
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return 2;
    }

    result = matches_pattern(argv[1], &matches);
    if (result != 0) {
        size_t length = regerror(result, NULL, NULL, 0);
        char *error_message;

        if (length == 0) {
            fputs("Regex error\n", stderr);
            return 1;
        }

        error_message = malloc(length);
        if (error_message == NULL) {
            fputs("Regex error: unable to allocate error buffer\n", stderr);
            return 1;
        }

        regerror(result, NULL, error_message, length);
        fprintf(stderr, "Regex error: %s\n", error_message);
        free(error_message);
        return 1;
    }

    puts(matches ? "Match" : "No match");
    return 0;
}