#include <stdio.h>
#include <stdlib.h>

void remove_spaces(char *str, size_t len) {
    if (str == NULL || len == 0) {
        return;
    }

    char *dst = str;
    char *src = str;
    char *end = str + len;

    while (*src != '\0' && src < end) {
        if (*src != ' ') {
            if (dst < end) {
                *dst = *src;
                dst++;
            }
        }
        src++;
    }
    
    if (dst < end) {
        *dst = '\0';
    } else {
        str[len - 1] = '\0';
    }
}

int main(void) {
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    remove_spaces(buffer, sizeof(buffer));

    if (fputs(buffer, stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}