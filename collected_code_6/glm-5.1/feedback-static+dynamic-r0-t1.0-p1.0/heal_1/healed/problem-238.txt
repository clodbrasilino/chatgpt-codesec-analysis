#include <stdio.h>
#include <string.h>

size_t count_substrings(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }

    size_t n = strnlen(str, max_len);
    return n * (n + 1) / 2;
}

int main(void) {
    const char *s = "abc";
    size_t count = count_substrings(s, 4);
    printf("%zu\n", count);
    return 0;
}