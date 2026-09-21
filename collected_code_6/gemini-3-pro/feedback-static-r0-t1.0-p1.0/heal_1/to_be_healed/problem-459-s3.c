#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void remove_uppercase_substrings(char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int reti;
    regmatch_t pmatch[1];
    const char *pattern = "[A-Z]+";

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return;
    }

    while (regexec(&regex, str, 1, pmatch, 0) == 0) {
        regoff_t start = pmatch[0].rm_so;
        regoff_t end = pmatch[0].rm_eo;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(str);

        memmove(str + start, str + end, len - end + 1);
    }

    regfree(&regex);
}

int main(void) {
    char test_str1[] = "HelloWORLDThisISaTEST";
    char test_str2[] = "no uppercase here";
    char test_str3[] = "ALLUPPERCASE";

    remove_uppercase_substrings(test_str1);
    printf("%s\n", test_str1);

    remove_uppercase_substrings(test_str2);
    printf("%s\n", test_str2);

    remove_uppercase_substrings(test_str3);
    printf("%s\n", test_str3);

    return 0;
}