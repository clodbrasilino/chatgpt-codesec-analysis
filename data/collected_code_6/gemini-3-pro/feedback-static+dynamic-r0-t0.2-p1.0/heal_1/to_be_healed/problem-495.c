#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void remove_lowercase_substrings(char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int reti;
    regmatch_t pmatch[1];

    reti = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (reti) {
        return;
    }

    while (regexec(&regex, str, 1, pmatch, 0) == 0) {
        int start = pmatch[0].rm_so;
        int end = pmatch[0].rm_eo;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        int len = strlen(str);

        memmove(&str[start], &str[end], len - end + 1);
    }

    regfree(&regex);
}

int main(void) {
    char str1[] = "Hello world! This is a TEST string 123.";
    char str2[] = "ALLCAPS123";
    char str3[] = "alllowercase";
    char str4[] = "MixEdCaSe";

    remove_lowercase_substrings(str1);
    printf("%s\n", str1);

    remove_lowercase_substrings(str2);
    printf("%s\n", str2);

    remove_lowercase_substrings(str3);
    printf("%s\n", str3);

    remove_lowercase_substrings(str4);
    printf("%s\n", str4);

    return 0;
}