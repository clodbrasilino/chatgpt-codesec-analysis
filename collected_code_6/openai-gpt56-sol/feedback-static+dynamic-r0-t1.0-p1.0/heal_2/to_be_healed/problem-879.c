#include <regex.h>
#include <stdbool.h>
#include <stdio.h>

static int matches_pattern(const char *input, bool *matched)
{
    regex_t regex;
    int result;

    if (input == NULL || matched == NULL) {
        return REG_BADPAT;
    }

    *matched = false;

    result = regcomp(&regex, "^a.*b$", REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return result;
    }

    result = regexec(&regex, input, 0, NULL, 0);
    if (result == 0) {
        *matched = true;
    }

    regfree(&regex);

    return (result == 0 || result == REG_NOMATCH) ? 0 : result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[])
{
    bool matched;
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 2;
    }

    result = matches_pattern(argv[1], &matched);
    if (result != 0) {
        fprintf(stderr, "Regex matching failed with error code %d\n", result);
        return 1;
    }

    printf("%s\n", matched ? "Match" : "No match");
    return 0;
}