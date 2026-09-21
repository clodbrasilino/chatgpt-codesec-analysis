#include <stdio.h>
#include <string.h>

size_t string_length(const char *str, size_t max_len) {
    size_t i = 0;
    while (i < max_len && str[i] != '\0') {
        i++;
    }
    return i;
}

int main() {
    const char *test_string = "Hello, World!";
    size_t max_len = 256;
    size_t length = string_length(test_string, max_len);
    if (length == max_len && strnlen(test_string, max_len) == max_len) {
        printf("Length: %zu (Possible overflow)\n", length);
    } else {
        printf("Length: %zu\n", length);
    }
    return 0;
}