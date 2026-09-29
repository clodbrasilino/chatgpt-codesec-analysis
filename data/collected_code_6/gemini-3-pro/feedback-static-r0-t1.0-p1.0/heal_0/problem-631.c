#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void swap_whitespace_underscore(char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int reti = regcomp(&regex, "[[:space:]_]", REG_EXTENDED);
    if (reti != 0) {
        return;
    }

    regmatch_t pmatch[1];
    size_t offset = 0;

    while (regexec(&regex, str + offset, 1, pmatch, 0) == 0) {
        size_t match_idx = offset + pmatch[0].rm_so;
        
        if (str[match_idx] == '_') {
            str[match_idx] = ' ';
        } else {
            str[match_idx] = '_';
        }
        
        offset += pmatch[0].rm_eo;
        if (pmatch[0].rm_so == pmatch[0].rm_eo) {
            offset += 1;
        }
    }

    regfree(&regex);
}

int main(void) {
    char text[] = "Hello_world\tthis is_a test";
    
    swap_whitespace_underscore(text);
    printf("%s\n", text);
    
    return 0;
}