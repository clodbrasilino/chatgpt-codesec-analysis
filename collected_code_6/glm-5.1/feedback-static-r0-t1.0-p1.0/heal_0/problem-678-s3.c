#include <stdio.h>
#include <stdlib.h>

void remove_spaces(char *str) {
    if (str == NULL) {
        return;
    }

    char *dst = str;
    char *src = str;

    while (*src != '\0') {
        if (*src != ' ') {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
}

int main(void) {
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    remove_spaces(buffer);

    if (fputs(buffer, stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}