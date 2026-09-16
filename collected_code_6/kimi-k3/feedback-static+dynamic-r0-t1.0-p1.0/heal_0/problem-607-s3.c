#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int find_pattern(const char *pattern, const char *text, regmatch_t *match) {
    regex_t regex;
    int ret;
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }
    
    ret = regexec(&regex, text, 1, match, 0);
    if (ret == REG_NOMATCH) {
        regfree(&regex);
        return 0;
    } else if (ret != 0) {
        regfree(&regex);
        return -1;
    }
    
    regfree(&regex);
    return 1;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *pattern = "brown";
    regmatch_t match;
    int result;
    
    result = find_pattern(pattern, text, &match);
    
    if (result == 1) {
        printf("Pattern found at position %ld to %ld\n", (long)match.rm_so, (long)match.rm_eo);
        printf("Matched text: %.*s\n", (int)(match.rm_eo - match.rm_so), text + match.rm_so);
    } else if (result == 0) {
        printf("Pattern not found\n");
    } else {
        printf("Error in regex processing\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}