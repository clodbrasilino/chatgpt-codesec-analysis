#include <regex.h>
#include <stdbool.h>
#include <stdio.h>

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
    } else if (result != REG_NOMATCH) {
        regfree(&regex);
        return result;
    }

    regfree(&regex);
    return 0;
}

int main(int argc, char *argv[])
{
    bool matches;
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 2;
    }

    result = matches_pattern(argv[1], &matches);
    if (result != 0) {
        char error_message[256];

        regerror(result, NULL, error_message, sizeof(error_message));
        fprintf(stderr, "Regex error: %s\n", error_message);
        return 1;
    }

    printf("%s\n", matches ? "Match" : "No match");
    return 0;
}