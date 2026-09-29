#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void remove_lowercase_substrings(char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int ret;
    regmatch_t pmatch[1];
    const char *pattern = "[a-z]+";

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return;
    }

    while (regexec(&regex, str, 1, pmatch, 0) == 0) {
        size_t match_start = pmatch[0].rm_so;
        size_t match_end = pmatch[0].rm_eo;
        size_t len = strlen(str);

        memmove(&str[match_start], &str[match_end], len - match_end + 1);
    }

    regfree(&regex);
}

int main(void) {
    char str1[] = "Hello world! This IS a TEST.";
    char str2[] = "ALLCAPS";
    char str3[] = "alllower";
    char str4[] = "MiXeD cAsE 123";

    remove_lowercase_substrings(str1);
    remove_lowercase_substrings(str2);
    remove_lowercase_substrings(str3);
    remove_lowercase_substrings(str4);

    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("%s\n", str3);
    printf("%s\n", str4);

    return 0;
}