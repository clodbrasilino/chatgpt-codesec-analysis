#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int search_literals_regex(const char *string, const char *literals[], size_t count, int *results) {
    regex_t regex;
    char *pattern = NULL;
    size_t pattern_size = 0;
    size_t pattern_len = 0;
    size_t i;
    int ret;
    
    if (string == NULL || literals == NULL || results == NULL || count == 0) {
        return -1;
    }
    
    for (i = 0; i < count; i++) {
        results[i] = 0;
    }
    
    for (i = 0; i < count; i++) {
        if (literals[i] == NULL) {
            return -1;
        }
        size_t lit_len = strnlen(literals[i], 4096);
        if (lit_len == 4096) {
            return -1;
        }
        pattern_size += lit_len * 2 + 3;
    }
    
    pattern = malloc(pattern_size + 1);
    if (pattern == NULL) {
        return -1;
    }
    
    pattern[0] = '\0';
    
    for (i = 0; i < count; i++) {
        if (i > 0) {
            if (pattern_len + 1 >= pattern_size) {
                free(pattern);
                return -1;
            }
            pattern[pattern_len++] = '|';
            pattern[pattern_len] = '\0';
        }
        
        if (pattern_len + 1 >= pattern_size) {
            free(pattern);
            return -1;
        }
        pattern[pattern_len++] = '(';
        pattern[pattern_len] = '\0';
        
        const char *src = literals[i];
        char *dst = pattern + pattern_len;
        const char *end = pattern + pattern_size;
        
        while (*src != '\0' && dst < end) {
            if (strchr(".^$*+?()[]{}|\\", *src) != NULL) {
                if (dst + 1 >= end) {
                    free(pattern);
                    return -1;
                }
                *dst++ = '\\';
            }
            *dst++ = *src++;
        }
        *dst = '\0';
        pattern_len = dst - pattern;
        
        if (pattern_len + 1 >= pattern_size) {
            free(pattern);
            return -1;
        }
        pattern[pattern_len++] = ')';
        pattern[pattern_len] = '\0';
    }
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    free(pattern);
    if (ret != 0) {
        return -1;
    }
    
    for (i = 0; i < count; i++) {
        size_t lit_len = strnlen(literals[i], 4096);
        if (lit_len == 4096) {
            regfree(&regex);
            return -1;
        }
        
        size_t single_size = lit_len * 2 + 1;
        char *single_pattern = malloc(single_size);
        if (single_pattern == NULL) {
            regfree(&regex);
            return -1;
        }
        
        const char *src = literals[i];
        char *dst = single_pattern;
        const char *end = single_pattern + single_size - 1;
        
        while (*src != '\0' && dst < end) {
            if (strchr(".^$*+?()[]{}|\\", *src) != NULL) {
                if (dst + 1 >= end) {
                    free(single_pattern);
                    regfree(&regex);
                    return -1;
                }
                *dst++ = '\\';
            }
            *dst++ = *src++;
        }
        *dst = '\0';
        
        regex_t single_regex;
        ret = regcomp(&single_regex, single_pattern, REG_EXTENDED);
        free(single_pattern);
        if (ret == 0) {
            ret = regexec(&single_regex, string, 0, NULL, 0);
            results[i] = (ret == 0) ? 1 : 0;
            regfree(&single_regex);
        }
    }
    
    regfree(&regex);
    return 0;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *literals[] = {"quick", "fox", "cat", "dog", "bird"};
    size_t count = sizeof(literals) / sizeof(literals[0]);
    int results[5];
    size_t i;
    int ret;
    
    ret = search_literals_regex(text, literals, count, results);
    
    if (ret != 0) {
        fprintf(stderr, "Error in search_literals_regex\n");
        return EXIT_FAILURE;
    }
    
    printf("Text: %s\n\n", text);
    printf("Search results:\n");
    
    for (i = 0; i < count; i++) {
        printf("  \"%s\": %s\n", literals[i], results[i] ? "found" : "not found");
    }
    
    return EXIT_SUCCESS;
}