#include <stdio.h>
#include <string.h>

int count_occurrences(const char *str, const char *pattern) {
    int count = 0;
    size_t pattern_len = strlen(pattern);
    if (pattern_len == 0) return 0;
    for (const char *p = str; (p = strstr(p, pattern)) != NULL; p += pattern_len) {
        count++;
    }
    return count;
}

int main() {
    const char *str = "1. list item 1. list item 1. list item 2. list item 2. list item 2. list item";
    const char *pattern = "std";
    int occurrences = count_occurrences(str, pattern);
    printf("The pattern '%s' occurs %d times.\n", pattern, occurrences);
    return 0;
}