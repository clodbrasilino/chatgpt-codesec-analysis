#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int search_literals_regex(const char *string, const char *literals[], size_t count, int *results) {
    regex_t regex;
    char pattern[1024];
    size_t i;
    int ret;
    
    if (string == NULL || literals == NULL || results == NULL || count == 0) {
        return -1;
    }
    
    for (i = 0; i < count; i++) {
        results[i] = 0;
    }
    
    pattern[0] = '\0';
    
    for (i = 0; i < count; i++) {
        if (literals[i] == NULL) {
            return -1;
        }
        
        if (i > 0) {
            if (strlen(pattern) + 1 >= sizeof(pattern)) {
                return -1;
            }
            strcat(pattern, "|");
        }
        
        if (strlen(pattern) + strlen(literals[i]) * 2 + 3 >= sizeof(pattern)) {
            return -1;
        }
        
        strcat(pattern, "(");
        
        const char *src = literals[i];
        char *dst = pattern + strlen(pattern);
        char *end = pattern + sizeof(pattern) - 1;
        
        while (*src != '\0' && dst < end) {
            if (strchr(".^$*+?()[]{}|\\", *src) != NULL) {
                if (dst + 1 >= end) {
                    return -1;
                }
                *dst++ = '\\';
            }
            *dst++ = *src++;
        }
        *dst = '\0';
        
        strcat(pattern, ")");
    }
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }
    
    for (i = 0; i < count; i++) {
        char single_pattern[512];
        const char *src = literals[i];
        char *dst = single_pattern;
        char *end = single_pattern + sizeof(single_pattern) - 1;
        
        while (*src != '\0' && dst < end) {
            if (strchr(".^$*+?()[]{}|\\", *src) != NULL) {
                if (dst + 1 >= end) {
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