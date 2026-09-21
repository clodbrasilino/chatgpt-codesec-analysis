#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void remove_uppercase_substrings(char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    if (regcomp(&regex, "[A-Z]+", REG_EXTENDED) != 0) {
        return;
    }

    regmatch_t pmatch[1];
    while (regexec(&regex, str, 1, pmatch, 0) == 0) {
        char *dest = str + pmatch[0].rm_so;
        const char *src = str + pmatch[0].rm_eo;
        
        while ((*dest++ = *src++) != '\0') {
        }
    }

    regfree(&regex);
}

int main(void) {
    char str1[] = "hello WORLD this IS a TEST string";
    
    remove_uppercase_substrings(str1);
    
    printf("%s\n", str1);
    
    return 0;
}