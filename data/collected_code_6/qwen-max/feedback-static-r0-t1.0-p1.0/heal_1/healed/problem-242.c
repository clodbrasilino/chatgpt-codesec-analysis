#include <stdio.h>
#include <string.h>

size_t count_characters(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        ++len;
    }
    return len;
}

int main() {
    const char *test_string = "Hello, World!";
    printf("Total characters: %zu\n", count_characters(test_string, sizeof("Hello, World!")));
    return 0;
}