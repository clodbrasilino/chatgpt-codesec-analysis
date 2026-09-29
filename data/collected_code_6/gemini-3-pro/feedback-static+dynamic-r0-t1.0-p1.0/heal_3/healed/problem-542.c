#if defined(__linux__) || defined(__APPLE__)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 8192

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

    size_t len = strnlen(input, MAX_INPUT_LEN);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char* p = input;
    char* q = result;
    size_t remaining = len + 1;
    regmatch_t pmatch[1];

    while (regexec(&regex, p, 1, pmatch, 0) == 0 && remaining > 1) {
        size_t match_len = pmatch[0].rm_so;
        
        if (match_len >= remaining) {
            match_len = remaining - 1;
        }
        
        if (match_len > 0) {
            for (size_t i = 0; i < match_len; i++) {
                q[i] = p[i];
            }
            q += match_len;
            remaining -= match_len;
        }
        
        if (remaining > 1) {
            *q = ':';
            q++;
            remaining--;
        }
        p += pmatch[0].rm_eo;
    }

    if (remaining > 0) {
        size_t p_len = strnlen(p, remaining - 1);
        for (size_t i = 0; i < p_len; i++) {
            q[i] = p[i];
        }
        q += p_len;
        *q = '\0';
    }

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