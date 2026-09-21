#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_multiple_spaces(char **str) {
    if (str == NULL || *str == NULL) {
        return -1;
    }

    regex_t regex;
    if (regcomp(&regex, "  +", REG_EXTENDED) != 0) {
        return -1;
    }

    char *current = *str;
    size_t new_len = strlen(current);
    char *new_str = malloc(new_len + 1);

    if (new_str == NULL) {
        regfree(&regex);
        return -1;
    }

    regmatch_t pmatch[1];
    char *dst = new_str;

    while (regexec(&regex, current, 1, pmatch, 0) == 0) {
        size_t match_start = pmatch[0].rm_so;
        size_t match_end = pmatch[0].rm_eo;
        
        memcpy(dst, current, match_start);
        dst += match_start;
        
        *dst = ' ';
        dst++;
        
        current += match_end;
    }

    size_t remaining = strlen(current);
    memcpy(dst, current, remaining + 1);

    free(*str);
    *str = new_str;

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *initial_text = "This   is  a    test string   with multiple     spaces.";
    char *text = malloc(strlen(initial_text) + 1);
    
    if (text == NULL) {
        return 1;
    }
    
    strcpy(text, initial_text);
    printf("Original: '%s'\n", text);

    if (remove_multiple_spaces(&text) == 0) {
        printf("Modified: '%s'\n", text);
    } else {
        printf("Error processing string.\n");
    }

    free(text);
    return 0;
}