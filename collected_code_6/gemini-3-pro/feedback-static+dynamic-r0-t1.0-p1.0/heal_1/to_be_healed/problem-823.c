#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int startsWithRegex(const char *string, const char *pattern) {
    if (string == NULL || pattern == NULL) {
        return 0;
    }

    regex_t regex;
    int ret;
    char *anchoredPattern;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(pattern);
    anchoredPattern = (char *)malloc(len + 2);
    if (anchoredPattern == NULL) {
        return 0;
    }

    anchoredPattern[0] = '^';
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(anchoredPattern + 1, pattern, len);
    anchoredPattern[len + 1] = '\0';

    ret = regcomp(&regex, anchoredPattern, REG_EXTENDED);
    free(anchoredPattern);
    
    if (ret) {
        return 0;
    }

    ret = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (!ret) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        return 0;
    }
}

int main(void) {
    const char *str1 = "Hello, world!";
    const char *pattern1 = "Hell";
    const char *pattern2 = "world";

    int result1 = startsWithRegex(str1, pattern1);
    int result2 = startsWithRegex(str1, pattern2);

    printf("'%s' starts with '%s': %s\n", str1, pattern1, result1 ? "true" : "false");
    printf("'%s' starts with '%s': %s\n", str1, pattern2, result2 ? "true" : "false");

    return 0;
}