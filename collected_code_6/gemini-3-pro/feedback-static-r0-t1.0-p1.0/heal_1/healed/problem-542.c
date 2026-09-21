#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_STR_LEN 4096

char* replace_chars(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strnlen(input, MAX_STR_LEN);
    if (len == MAX_STR_LEN) {
        return NULL;
    }

    regex_t regex;
    int reti;
    const char* pattern = "[ ,.]";
    
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return NULL;
    }

    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char* p = input;
    char* q = result;
    size_t remaining_space = len + 1;
    regmatch_t pmatch[1];

    while (regexec(&regex, p, 1, pmatch, 0) == 0 && remaining_space > 1) {
        size_t match_len = pmatch[0].rm_so;
        
        if (match_len >= remaining_space) {
            match_len = remaining_space - 1;
        }

        for (size_t i = 0; i < match_len; i++) {
            *q++ = p[i];
        }
        
        remaining_space -= match_len;

        if (remaining_space > 1) {
            *q++ = ':';
            remaining_space--;
        }

        p += pmatch[0].rm_eo;
    }

    size_t copy_len = strnlen(p, remaining_space - 1);
    for (size_t i = 0; i < copy_len; i++) {
        *q++ = p[i];
    }
    *q = '\0';

    regfree(&regex);
    return result;
}

int main(void) {
    const char* original_str = "Hello, world. This is a test string.";
    
    char* modified_str = replace_chars(original_str);
    
    if (modified_str != NULL) {
        printf("Original: %s\n", original_str);
        printf("Modified: %s\n", modified_str);
        
        free(modified_str);
    } else {
        printf("An error occurred during replacement.\n");
    }

    return 0;
}