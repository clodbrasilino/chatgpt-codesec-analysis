#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int count_matches(const char *pattern, const char *text, int *count)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int ret;

    if (pattern == NULL || text == NULL || count == NULL) {
        return -1;
    }

    *count = 0;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "regcomp failed: %s\n", errbuf);
        return -1;
    }

    cursor = text;
    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char errbuf[256];
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "regexec failed: %s\n", errbuf);
            regfree(&regex);
            return -1;
        }
        (*count)++;
        if (match.rm_eo == 0) {
            cursor++;
        } else {
            cursor += match.rm_eo;
        }
    }

    regfree(&regex);
    return 0;
}

int analyze_string(const char *text)
{
    int upper = 0;
    int lower = 0;
    int digit = 0;
    int special = 0;

    if (text == NULL) {
        fprintf(stderr, "analyze_string: NULL input\n");
        return -1;
    }

    if (count_matches("[A-Z]", text, &upper) != 0) {
        return -1;
    }
    if (count_matches("[a-z]", text, &lower) != 0) {
        return -1;
    }
    if (count_matches("[0-9]", text, &digit) != 0) {
        return -1;
    }
    if (count_matches("[^A-Za-z0-9]", text, &special) != 0) {
        return -1;
    }

    printf("Input string: %s\n", text);
    printf("Uppercase characters: %d\n", upper);
    printf("Lowercase characters: %d\n", lower);
    printf("Numeric characters: %d\n", digit);
    printf("Special characters: %d\n", special);

    return 0;
}

int main(void)
{
    const char *sample = "Hello World! 123 @C_programming#2024";

    if (analyze_string(sample) != 0) {
        fprintf(stderr, "Analysis failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}