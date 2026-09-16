#include <stdio.h>
#include <stddef.h>

size_t string_length(const char *str);

size_t string_length(const char *str) {
    const char *s;
    if (str == NULL) {
        return 0;
    }
    for (s = str; *s; ++s) {
    }
    return (size_t)(s - str);
}

int main(void) {
    const char *test_string = "Hello, World!";
    size_t len;

    len = string_length(test_string);
    printf("%zu\n", len);

    len = string_length(NULL);
    printf("%zu\n", len);

    return 0;
}