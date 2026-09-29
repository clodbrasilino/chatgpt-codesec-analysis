#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void swap_whitespace_underscore(char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ _]", REG_EXTENDED);
    if (ret != 0) {
        return;
    }

    regmatch_t pmatch[1];
    char *cursor = str;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        if (cursor[pmatch[0].rm_so] == ' ') {
            cursor[pmatch[0].rm_so] = '_';
        } else if (cursor[pmatch[0].rm_so] == '_') {
            cursor[pmatch[0].rm_so] = ' ';
        }
        cursor += pmatch[0].rm_eo;
    }

    regfree(&regex);
}

int main(void) {
    char str[] = "Hello_world this is_a test";
    
    printf("Original: %s\n", str);
    
    swap_whitespace_underscore(str);
    
    printf("Modified: %s\n", str);
    
    return 0;
}