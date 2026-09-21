#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int remove_non_alnum(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return -1;
    }
    size_t len = strnlen(str, size);
    size_t write = 0;
    for (size_t i = 0; i < len; ++i) {
        unsigned char c = (unsigned char)str[i];
        if (isalnum(c)) {
            if (write < size - 1) {
                str[write] = c;
                ++write;
            } else {
                break;
            }
        }
    }
    str[write] = '\0';
    return 0;
}

int main(void) {
    char text[] = "Hello, World! 123";
    if (remove_non_alnum(text, sizeof(text)) != 0) {
        return EXIT_FAILURE;
    }
    printf("%s\n", text);
    return EXIT_SUCCESS;
}