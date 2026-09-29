#include <stdio.h>
#include <string.h>

int count_occurrences(const char *str, const char *target, size_t str_len) {
    int count = 0;
    const char *p = str;
    size_t target_len = strlen(target);

    while (p - str + target_len <= str_len && (p = strstr(p, target)) != NULL) {
        count++;
        p += target_len;
    }
    return count;
}

int main() {
    const char *input = "1. list item 1. list item 1. list item 2. list item 2. list item 2. list item";
    const char *target = "std";
    size_t input_len = strlen(input);

    int occurrences = count_occurrences(input, target, input_len);
    printf("Occurrences of '%s' in the string: %d\n", target, occurrences);

    return 0;
}