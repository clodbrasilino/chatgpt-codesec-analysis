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
    size_t max_len = 256; // Set a fixed maximum length
    printf("Length: %zu\n", string_length(test_string, max_len));
    return 0;
}