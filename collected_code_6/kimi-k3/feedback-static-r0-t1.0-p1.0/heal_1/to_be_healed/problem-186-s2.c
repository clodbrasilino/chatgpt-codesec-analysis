#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int search_literals_regex(const char *string, const char *literals[], size_t count, int *results) {
    regex_t regex;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            if (strlen(pattern) + 1 >= sizeof(pattern)) {
                return -1;
            }
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strcat(pattern, "|");
        }
        
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(pattern) + strlen(literals[i]) * 2 + 3 >= sizeof(pattern)) {
            return -1;
        }
        
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
         */
        strcat(pattern, "(");
        
        const char *src = literals[i];
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        char *dst = pattern + strlen(pattern);
        /* Possible weaknesses found:
         *  Variable 'end' can be declared as pointer to const [constVariablePointer]
         */
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
        
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
         */
        strcat(pattern, ")");
    }
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }
    
    for (i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char single_pattern[512];
        const char *src = literals[i];
        char *dst = single_pattern;
        /* Possible weaknesses found:
         *  Variable 'end' can be declared as pointer to const [constVariablePointer]
         */
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