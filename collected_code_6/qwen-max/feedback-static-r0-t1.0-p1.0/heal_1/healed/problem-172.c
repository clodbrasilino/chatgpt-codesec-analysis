#include <stdio.h>
#include <string.h>

int count_substring(const char *str, const char *sub) {
    int count = 0;
    size_t sub_len = strlen(sub);
    for (const char *p = str; (p = strstr(p, sub)) != NULL; p += sub_len) {
        ++count;
    }
    return count;
}

int main() {
    const char *input = "1. list item 1. list item 1. list item 2. list item 2. list item 2. list item";
    const char *pattern = "std";
    int occurrences = count_substring(input, pattern);
    printf("Occurrences of 'std': %d\n", occurrences);
    return 0;
}