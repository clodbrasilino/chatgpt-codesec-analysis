#include <stdio.h>
#include <string.h>

size_t string_length(const char *str) {
    return strlen(str);
}

int main() {
    const char *test_string = "Hello, World!";
    printf("Length: %zu\n", string_length(test_string));
    return 0;
}