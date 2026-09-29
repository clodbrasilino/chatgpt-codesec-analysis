#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count_non_empty_substrings(const char *str, size_t max_len) {
    size_t len = strnlen(str, max_len);
    return len * (len + 1) / 2;
}

int main() {
    const char test_str[] = "abc";
    size_t count = count_non_empty_substrings(test_str, sizeof(test_str) - 1);
    printf("Number of non-empty substrings: %zu\n", count);
    return 0;
}