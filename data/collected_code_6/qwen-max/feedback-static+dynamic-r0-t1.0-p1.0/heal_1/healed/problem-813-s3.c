#include <stdio.h>
#include <string.h>

size_t string_length(const char *str, size_t max_length) {
    const char *end = memchr(str, '\0', max_length);
    return end ? (size_t)(end - str) : max_length;
}

int main() {
    const char *test_string = "Hello, World!";
    printf("Length: %zu\n", string_length(test_string, 1024));
    return 0;
}