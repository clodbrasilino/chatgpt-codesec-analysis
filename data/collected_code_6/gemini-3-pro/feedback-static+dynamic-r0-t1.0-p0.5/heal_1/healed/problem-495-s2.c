#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void remove_lowercase_substrings(char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    if (regcomp(&regex, "[a-z]+", REG_EXTENDED) != 0) {
        return;
    }

    regmatch_t pmatch[1];
    while (regexec(&regex, str, 1, pmatch, 0) == 0) {
        char *dst = str + pmatch[0].rm_so;
        char *src = str + pmatch[0].rm_eo;
        
        while ((*dst++ = *src++) != '\0') {
        }
    }

    regfree(&regex);
}

int main(void) {
    char test_str1[] = "Hello world! This is a TEST string 123.";
    char test_str2[] = "ALLUPPERCASE";
    char test_str3[] = "alllowercase";
    char test_str4[] = "M1x3d C4s3";

    remove_lowercase_substrings(test_str1);
    printf("%s\n", test_str1);

    remove_lowercase_substrings(test_str2);
    printf("%s\n", test_str2);

    remove_lowercase_substrings(test_str3);
    printf("%s\n", test_str3);

    remove_lowercase_substrings(test_str4);
    printf("%s\n", test_str4);

    return 0;
}