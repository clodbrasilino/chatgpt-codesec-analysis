#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_multiple_spaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }
    
    regex_t regex;
    int ret = regcomp(&regex, " +", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }
    
    size_t len = strlen(input);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }
    
    const char *src = input;
    char *dst = result;
    regmatch_t match;
    /* Possible weaknesses found:
     *  The scope of the variable 'last_end' can be reduced. [variableScope]
     *  Variable 'last_end' is assigned a value that is never used. [unreadVariable]
     */
    int last_end = 0;
    
    while (regexec(&regex, src, 1, &match, 0) == 0) {
        size_t match_start = match.rm_so;
        size_t match_end = match.rm_eo;
        
        if (match_start > 0) {
            memcpy(dst, src, match_start);
            dst += match_start;
        }
        
        *dst++ = ' ';
        
        src += match_end;
        /* Possible weaknesses found:
         *  Value stored to 'last_end' is never read [deadcode.DeadStores]
         *  Variable 'last_end' is assigned a value that is never used. [unreadVariable]
         */
        last_end = match_end;
    }
    
    strcpy(dst, src);
    
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test = "This  is   a    test   string";
    char *cleaned = remove_multiple_spaces(test);
    
    if (cleaned != NULL) {
        printf("Original: '%s'\n", test);
        printf("Cleaned:  '%s'\n", cleaned);
        free(cleaned);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}