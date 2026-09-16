#include <stdio.h>
#include <string.h>

size_t count_characters(const char *str) {
    if (str == NULL) {
        return 0;
    }
    return strlen(str);
}

int main() {
    const char *test_string = "Hello, world!";
    size_t length = count_characters(test_string);
    printf("Total characters: %zu\n", length);
    return 0;
}