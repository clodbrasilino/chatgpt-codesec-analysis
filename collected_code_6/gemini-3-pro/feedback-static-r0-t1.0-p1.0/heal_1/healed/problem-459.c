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
    
    reti = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (reti) {
        return;
    }

    while (regexec(&regex, str, 1, pmatch, 0) == 0) {
        size_t match_start = pmatch[0].rm_so;
        size_t match_end = pmatch[0].rm_eo;
        
        size_t i = match_start;
        size_t j = match_end;
        while ((str[i++] = str[j++]) != '\0');
    }

    regfree(&regex);
}

int main(void) {
    char str1[] = "Hello World! THIS is a TEST string.";
    char str2[] = "lowercaseonly";
    char str3[] = "ALLUPPERCASE";
    char str4[] = "MixedCASEstring";

    remove_uppercase_substrings(str1);
    printf("Result 1: %s\n", str1);

    remove_uppercase_substrings(str2);
    printf("Result 2: %s\n", str2);

    remove_uppercase_substrings(str3);
    printf("Result 3: %s\n", str3);

    remove_uppercase_substrings(str4);
    printf("Result 4: %s\n", str4);

    return 0;
}