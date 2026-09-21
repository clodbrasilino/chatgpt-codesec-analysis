#include <stdio.h>
#include <string.h>

size_t count_characters(const char *str, size_t max_size) {
    size_t length = 0;
    for (size_t i = 0; i < max_size && str[i] != '\0'; ++i) {
        length++;
    }
    return length;
}

int main() {
    const char *test_string = "Hello, World!";
    size_t max_size = 14;
    printf("Total characters: %zu\n", count_characters(test_string, max_size));
    return 0;
}