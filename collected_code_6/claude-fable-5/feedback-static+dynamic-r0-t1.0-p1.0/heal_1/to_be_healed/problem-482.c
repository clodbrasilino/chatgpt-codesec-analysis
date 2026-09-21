#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCH_LEN 256

int find_sequences(const char *input)
{
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[A-Z][a-z]+";
    const char *cursor;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_MATCH_LEN];
    int ret;
    int found;
    /* Possible weaknesses found:
     *  The scope of the variable 'length' can be reduced. [variableScope]
     */
    size_t length;

    if (input == NULL) {
        fprintf(stderr, "Error: input string is NULL\n");
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char errbuf[128];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Error: failed to compile regex: %s\n", errbuf);
        return -1;
    }

    found = 0;
    cursor = input;

    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char errbuf[128];
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "Error: regex execution failed: %s\n", errbuf);
            regfree(&regex);
            return -1;
        }

        length = (size_t)(match.rm_eo - match.rm_so);
        if (length >= sizeof(buffer)) {
            length = sizeof(buffer) - 1;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buffer, cursor + match.rm_so, length);
        buffer[length] = '\0';
        printf("Found match: %s\n", buffer);
        found++;

        cursor += match.rm_eo;
    }

    regfree(&regex);

    if (found == 0) {
        printf("No matches found.\n");
    }

    return found;
}

int main(void)
{
    const char *test_string = "HelloWorld this Is a TestString with Mixed caseWords";
    int result;

    printf("Input: %s\n", test_string);

    result = find_sequences(test_string);
    if (result < 0) {
        fprintf(stderr, "Error: sequence search failed\n");
        return EXIT_FAILURE;
    }

    printf("Total matches: %d\n", result);

    return EXIT_SUCCESS;
}