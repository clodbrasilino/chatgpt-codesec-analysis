#include <stdio.h>
#include <string.h>

size_t string_length(const char *str, size_t max_len) {
    size_t i = 0;
    while (i < max_len && str[i] != '\0') {
        i++;
    }
    return i < max_len ? i : max_len;
}

int main() {
    const char *test_string = "Hello, World!";
    size_t max_len = 256;
    printf("Length: %zu\n", string_length(test_string, max_len));
    return 0;
}