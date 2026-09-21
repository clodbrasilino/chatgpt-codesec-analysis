#include <regex.h>
#include <stdbool.h>
#include <stdio.h>

static bool starts_with_vowel(const char *string)
{
    regex_t regex;
    int result;

    if (string == NULL) {
        return false;
    }

    result = regcomp(&regex, "^[AEIOUaeiou]", REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return false;
    }

    result = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return 1;
        }
        fputs("No input provided.\n", stderr);
        return 1;
    }

    puts(starts_with_vowel(input) ? "Starts with a vowel" : "Does not start with a vowel");
    return 0;
}