#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* replace_chars(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int reti;
    const char* pattern = "[ ,.]";
    
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return NULL;
    }

    size_t len = strlen(input);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char* p = input;
    char* q = result;
    regmatch_t pmatch[1];

    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        size_t match_len = pmatch[0].rm_so;
        memcpy(q, p, match_len);
        q += match_len;
        *q = ':';
        q++;
        p += pmatch[0].rm_eo;
    }

    strcpy(q, p);

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