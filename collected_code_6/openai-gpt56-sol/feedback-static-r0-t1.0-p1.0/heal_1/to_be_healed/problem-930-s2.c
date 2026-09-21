#include <regex.h>
#include <stdbool.h>
#include <stdio.h>

static int matches_pattern(const char *string, bool *matches)
{
    regex_t regex;
    const char *pattern = "^ab*$";
    int result;

    if (string == NULL || matches == NULL) {
        return REG_INVARG;
    }

    *matches = false;

    result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return result;
    }

    result = regexec(&regex, string, 0, NULL, 0);
    if (result == 0) {
        *matches = true;
    } else if (result != REG_NOMATCH) {
        regfree(&regex);
        return result;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    bool matches;
    int result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            perror("fgets");
        } else {
            fputs("No input provided\n", stderr);
        }
        return 1;
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] != '\0') {
        fputs("Input is too long\n", stderr);
        return 1;
    }

    result = matches_pattern(input, &matches);
    if (result != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char message[256];
        regerror(result, NULL, message, sizeof(message));
        fprintf(stderr, "Regex error: %s\n", message);
        return 1;
    }

    puts(matches ? "Match" : "No match");
    return 0;
}