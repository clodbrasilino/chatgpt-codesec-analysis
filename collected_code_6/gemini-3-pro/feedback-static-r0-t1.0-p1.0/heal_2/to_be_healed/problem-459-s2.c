#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void remove_uppercase_substrings(char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int ret;
    regmatch_t pmatch[1];

    ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        return;
    }

    while (regexec(&regex, str, 1, pmatch, 0) == 0) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining_len = strlen(str + pmatch[0].rm_eo);
        memmove(str + pmatch[0].rm_so, str + pmatch[0].rm_eo, remaining_len + 1);
    }

    regfree(&regex);
}

int main(void) {
    char str1[] = "hello WORLD this IS a TEST string";
    
    remove_uppercase_substrings(str1);
    
    printf("%s\n", str1);
    
    return 0;
}