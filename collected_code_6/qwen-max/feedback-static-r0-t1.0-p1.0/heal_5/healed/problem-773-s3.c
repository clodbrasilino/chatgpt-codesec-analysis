#include <stdio.h>
#include <string.h>

void find_substrings(const char *str, size_t str_len, const char *substr, size_t substr_len) {
    for (size_t i = 0; i <= str_len - substr_len; i++) {
        if (strncmp(&str[i], substr, substr_len) == 0) {
            printf("Found at position: %zu\n", i);
        }
    }
}

int main() {
    const char *str = "This is a test string to test substring search.";
    const char *substr = "test";
    size_t str_len = sizeof(str) - 1;
    size_t substr_len = sizeof(substr) - 1;
    find_substrings(str, str_len, substr, substr_len);
    return 0;
}