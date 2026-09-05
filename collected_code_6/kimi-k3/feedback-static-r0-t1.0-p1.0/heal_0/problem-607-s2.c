#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int find_literal_regex(const char *str, const char *pattern, size_t *start, size_t *end) {
    regex_t regex;
    regmatch_t match;
    char *escaped_pattern;
    size_t i, j;
    size_t pattern_len;
    int ret;
    
    if (str == NULL || pattern == NULL || start == NULL || end == NULL) {
        return -1;
    }
    
    pattern_len = strlen(pattern);
    if (pattern_len == 0) {
        return -1;
    }
    
    escaped_pattern = malloc(pattern_len * 2 + 1);
    if (escaped_pattern == NULL) {
        return -1;
    }
    
    for (i = 0, j = 0; i < pattern_len; i++) {
        if (strchr("^$.[]|()?*+{}\\", pattern[i]) != NULL) {
            escaped_pattern[j++] = '\\';
        }
        escaped_pattern[j++] = pattern[i];
    }
    escaped_pattern[j] = '\0';
    
    ret = regcomp(&regex, escaped_pattern, REG_EXTENDED);
    free(escaped_pattern);
    
    if (ret != 0) {
        return -1;
    }
    
    ret = regexec(&regex, str, 1, &match, 0);
    regfree(&regex);
    
    if (ret != 0) {
        return -1;
    }
    
    if (match.rm_so < 0 || match.rm_eo < 0) {
        return -1;
    }
    
    *start = (size_t)match.rm_so;
    *end = (size_t)match.rm_eo;
    
    return 0;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *pattern = "brown fox";
    size_t start, end;
    
    if (find_literal_regex(text, pattern, &start, &end) == 0) {
        printf("Pattern found at position %zu to %zu\n", start, end);
        printf("Matched text: %.*s\n", (int)(end - start), text + start);
    } else {
        printf("Pattern not found\n");
    }
    
    return 0;
}