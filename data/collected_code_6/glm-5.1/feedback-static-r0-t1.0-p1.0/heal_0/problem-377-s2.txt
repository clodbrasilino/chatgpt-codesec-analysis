#include <stdio.h>
#include <stdlib.h>

void remove_char(char *str, char c) {
    if (str == NULL) {
        return;
    }
    char *dst = str;
    while (*str) {
        if (*str != c) {
            *dst++ = *str;
        }
        str++;
    }
    *dst = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <char>\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (argv[2][1] != '\0') {
        fprintf(stderr, "Error: Second argument must be a single character.\n");
        return EXIT_FAILURE;
    }
    char c = argv[2][0];
    size_t len = 0;
    while (argv[1][len] != '\0') {
        len++;
    }
    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return EXIT_FAILURE;
    }
    char *p = buffer;
    const char *s = argv[1];
    while (*s) {
        *p++ = *s++;
    }
    *p = '\0';
    remove_char(buffer, c);
    printf("%s\n", buffer);
    free(buffer);
    buffer = NULL;
    return EXIT_SUCCESS;
}