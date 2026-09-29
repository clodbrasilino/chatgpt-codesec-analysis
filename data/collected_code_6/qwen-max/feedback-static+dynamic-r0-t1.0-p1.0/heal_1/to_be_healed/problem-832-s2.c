#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <limits.h>

int find_max_value(const char *input) {
    regex_t regex;
    regmatch_t matches[1];
    /* Possible weaknesses found:
     *  The scope of the variable 'current' can be reduced. [variableScope]
     */
    int max = INT_MIN, current;
    const char *pattern = R"(\d+)";
    
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        return -1;
    }

    char *str = (char *)input;
    while (regexec(&regex, str, 1, matches, 0) == 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char match[matches[0].rm_eo - matches[0].rm_so + 1];
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(match, &str[matches[0].rm_so], matches[0].rm_eo - matches[0].rm_so);
        match[matches[0].rm_eo - matches[0].rm_so] = '\0';
        /* Possible weaknesses found:
         *  call to undeclared function 'atoi'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'atoi' [-Wimplicit-function-declaration]
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        current = atoi(match);
        if (current > max) {
            max = current;
        }
        str += matches[0].rm_eo;
    }

    regfree(&regex);
    return max == INT_MIN ? -1 : max;
}

int main() {
    const char *test_str = "The maximum value in this string is 12345, but it also contains 100, 200, and 999.";
    int result = find_max_value(test_str);
    printf("Maximum value: %d\n", result);
    return 0;
}