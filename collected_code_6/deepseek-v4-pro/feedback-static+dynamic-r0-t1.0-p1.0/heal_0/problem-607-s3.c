#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int regex_search(const char *string, const char *pattern, regmatch_t *pmatch, int nmatch) {
    regex_t regex;
    int ret;
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }
    
    ret = regexec(&regex, string, nmatch, pmatch, 0);
    regfree(&regex);
    
    if (ret == 0) {
        return 0;
    } else if (ret == REG_NOMATCH) {
        return 1;
    } else {
        return -2;
    }
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *pattern = "brown";
    regmatch_t matches[1];
    int result;
    
    result = regex_search(text, pattern, matches, 1);
    
    if (result == 0) {
        printf("Pattern found at position %d\n", (int)matches[0].rm_so);
        printf("Match length: %d\n", (int)(matches[0].rm_eo - matches[0].rm_so));
        printf("Matched text: ");
        for (int i = matches[0].rm_so; i < matches[0].rm_eo; i++) {
            putchar(text[i]);
        }
        putchar('\n');
    } else if (result == 1) {
        printf("Pattern not found\n");
    } else if (result == -1) {
        printf("Regex compilation failed\n");
    } else {
        printf("Regex execution error\n");
    }
    
    return 0;
}