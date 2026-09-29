#include <stdio.h>
#include <string.h>
#include <regex.h>

int find_pattern_location(const char *text, const char *pattern) {
    regex_t regex;
    regmatch_t match;

    if (regcomp(&regex, pattern, REG_NEWLINE) != 0) {
        return -1;
    }

    if (regexec(&regex, text, 1, &match, 0) == 0) {
        int offset = match.rm_so;
        regfree(&regex);
        return offset;
    } else {
        regfree(&regex);
        return -1;
    }
}

int main() {
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *pattern = "fox";
    int location = find_pattern_location(text, pattern);

    if (location != -1) {
        printf("Pattern found at location: %d\n", location);
    } else {
        printf("Pattern not found\n");
    }

    return 0;
}