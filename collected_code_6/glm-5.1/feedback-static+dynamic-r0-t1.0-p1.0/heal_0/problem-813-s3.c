#include <stdio.h>
#include <stdlib.h>

size_t string_length(const char *str) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    
    const char *valid_str = "Hello, World!";
    const char *empty_str = "";
    const char *null_str = NULL;

    size_t len1 = string_length(valid_str);
    size_t len2 = string_length(empty_str);
    size_t len3 = string_length(null_str);

    printf("Length of valid_str: %zu\n", len1);
    printf("Length of empty_str: %zu\n", len2);
    printf("Length of null_str: %zu\n", len3);

    return EXIT_SUCCESS;
}