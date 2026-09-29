#include <stdio.h>
#include <string.h>

size_t count_chars(const char *str, size_t max_size) {
    return strnlen(str, max_size);
}

int main() {
    const char *input = "Hello, world!";
    size_t length = count_chars(input, sizeof("Hello, world!"));
    printf("Total characters: %zu\n", length);
    return 0;
}