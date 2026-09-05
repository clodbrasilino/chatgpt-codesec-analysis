#include <stdio.h>
#include <string.h>

size_t count_characters(const char *str) {
    if (str == NULL) {
        return 0;
    }
    size_t count = 0;
    while (*str != '\0') {
        count++;
        str++;
    }
    return count;
}

int main(void) {
    const char *text = "Hello, World!";
    size_t len = count_characters(text);
    printf("%zu\n", len);
    return 0;
}