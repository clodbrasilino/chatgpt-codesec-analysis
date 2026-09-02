#include <stdio.h>
#include <string.h>

size_t string_length(const char *str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int main() {
    const char *test_string = "Hello, World!";
    size_t len = string_length(test_string);
    printf("Length of the string: %zu\n", len);
    return 0;
}