#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

int starts_with_regex(const char *str, const char *pattern) {
    regex_t regex;
    int ret;
    char *anchored_pattern = NULL;
    size_t pattern_len;
    regmatch_t match;
    
    if (str == NULL || pattern == NULL) {
        return 0;
    }
    
    pattern_len = strlen(pattern);
    
    if (pattern_len >= SIZE_MAX - 2) {
        return 0;
    }
    
    anchored_pattern = malloc(pattern_len + 2);
    if (anchored_pattern == NULL) {
        return 0;
    }
    
    anchored_pattern[0] = '^';
    if (pattern_len > 0) {
        memcpy(anchored_pattern + 1, pattern, pattern_len);
    }
    anchored_pattern[pattern_len + 1] = '\0';
    
    ret = regcomp(&regex, anchored_pattern, REG_EXTENDED);
    free(anchored_pattern);
    if (ret != 0) {
        return 0;
    }
    
    ret = regexec(&regex, str, 1, &match, 0);
    regfree(&regex);
    
    if (ret == 0 && match.rm_so == 0) {
        return 1;
    }
    
    return 0;
}

int main(void) {
    const char *test_string = "hello world";
    const char *pattern1 = "hello";
    const char *pattern2 = "world";
    const char *pattern3 = "h.*o";
    const char *pattern4 = "z.*";
    
    printf("Test 1: %s starts with %s: %s\n", test_string, pattern1, 
           starts_with_regex(test_string, pattern1) ? "yes" : "no");
    printf("Test 2: %s starts with %s: %s\n", test_string, pattern2, 
           starts_with_regex(test_string, pattern2) ? "yes" : "no");
    printf("Test 3: %s starts with %s: %s\n", test_string, pattern3, 
           starts_with_regex(test_string, pattern3) ? "yes" : "no");
    printf("Test 4: %s starts with %s: %s\n", test_string, pattern4, 
           starts_with_regex(test_string, pattern4) ? "yes" : "no");
    printf("Test 5: NULL string: %s\n", 
           starts_with_regex(NULL, pattern1) ? "yes" : "no");
    printf("Test 6: NULL pattern: %s\n", 
           starts_with_regex(test_string, NULL) ? "yes" : "no");
    
    return 0;
}