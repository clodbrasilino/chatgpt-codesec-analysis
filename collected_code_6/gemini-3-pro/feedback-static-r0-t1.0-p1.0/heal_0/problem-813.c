#include <stdio.h>
#include <stddef.h>

size_t string_length(const char *str);

size_t string_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }

    return length;
}

int main(void) {
    const char *valid_string = "Hello, World!";
    const char *null_string = NULL;

    printf("%zu\n", string_length(valid_string));
    printf("%zu\n", string_length(null_string));

    return 0;
}