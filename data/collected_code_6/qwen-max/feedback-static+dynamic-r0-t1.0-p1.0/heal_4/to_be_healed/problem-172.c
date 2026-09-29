#include <stdio.h>
#include <string.h>

int count_substring(const char *str, const char *sub) {
    int count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t sub_len = strlen(sub);
    if (sub_len == 0) return 0;
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