#include <stdio.h>
#include <string.h>

size_t count_characters(const char *str, size_t max_size) {
    if (str == NULL || max_size == 0) {
        return 0;
    }
    size_t i = 0;
    for (; i < max_size && str[i] != '\0'; ++i) {}
    return i;
}

int main() {
    const char *test_string = "Hello, world!";
    size_t length = count_characters(test_string, 13);
    printf("Total characters: %zu\n", length);
    return 0;
}