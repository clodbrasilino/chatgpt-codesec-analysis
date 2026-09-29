#include <stdio.h>
#include <string.h>

void find_substrings(const char *str, const char *pattern) {
    size_t str_len = strnlen(str, 1024);
    size_t pattern_len = strnlen(pattern, 1024);
    if (pattern_len == 0 || pattern_len > str_len) return;

    for (size_t i = 0; i <= str_len - pattern_len; i++) {
        if (strncmp(&str[i], pattern, pattern_len) == 0) {
            printf("Substring found at position: %zu\n", i);
        }
    }
}

int main() {
    const char *text = "This is a test string to find the substring test in this text.";
    const char *substr = "test";
    find_substrings(text, substr);
    return 0;
}