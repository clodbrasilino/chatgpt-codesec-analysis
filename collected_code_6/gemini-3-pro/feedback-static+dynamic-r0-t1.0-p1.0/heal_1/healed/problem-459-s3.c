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
        
        char *dst = str + start;
        const char *src = str + end;
        while ((*dst++ = *src++)) {
        }
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