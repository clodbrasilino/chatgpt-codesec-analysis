#include <stdio.h>
#include <stdlib.h>

void remove_char(char *str, char c) {
    if (str == NULL) {
        return;
    }

    char *dst = str;
    char *src = str;

    while (*src != '\0') {
        if (*src != c) {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <char>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[2][0] == '\0') {
        fprintf(stderr, "Error: Missing character argument.\n");
        return EXIT_FAILURE;
    }

    remove_char(argv[1], argv[2][0]);

    printf("%s\n", argv[1]);

    return EXIT_SUCCESS;
}