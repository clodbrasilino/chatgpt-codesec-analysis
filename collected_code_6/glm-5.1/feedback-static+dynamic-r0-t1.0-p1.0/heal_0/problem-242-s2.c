#include <stdio.h>
#include <stddef.h>

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
    const char *test_str = "Hello, World!";
    size_t length = count_characters(test_str);

    printf("%zu\n", length);
    return 0;
}