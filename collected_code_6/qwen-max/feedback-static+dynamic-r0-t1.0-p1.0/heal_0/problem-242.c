#include <stdio.h>
#include <string.h>

size_t count_characters(const char *str) {
    return strlen(str);
}

int main() {
    const char *test_string = "Hello, World!";
    printf("Total characters: %zu\n", count_characters(test_string));
    return 0;
}