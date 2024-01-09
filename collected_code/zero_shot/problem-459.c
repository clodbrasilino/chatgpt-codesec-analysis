#include <stdio.h>
#include <regex.h>

void removeUppercaseSubstrings(char* str) {
    regex_t regex;
    regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    regmatch_t match;
    
    while (regexec(&regex, str, 1, &match, 0) != REG_NOMATCH) {
        int start = match.rm_so;
        int end = match.rm_eo;
        
        for (int i = start; i < end; i++) {
            str[i] = ' ';
        }
    }
    
    regfree(&regex);
}

int main() {
    char str[] = "Hello, World! This is a TEST string.";
    removeUppercaseSubstrings(str);
    printf("%s\n", str);
    
    return 0;
}