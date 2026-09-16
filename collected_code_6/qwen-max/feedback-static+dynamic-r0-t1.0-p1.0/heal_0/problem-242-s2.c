#include <stdio.h>
#include <string.h>

size_t count_chars(const char *str) {
    return strlen(str);
}

int main() {
    const char *input = "Hello, world!";
    size_t length = count_chars(input);
    printf("Total characters: %zu\n", length);
    return 0;
}