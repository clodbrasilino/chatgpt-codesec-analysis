#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if (argv[2][0] == '\0' || argv[2][1] != '\0') {
        fprintf(stderr, "Error: Second argument must be a single character.\n");
        return EXIT_FAILURE;
    }
    char c = argv[2][0];
    size_t len = strnlen(argv[1], SIZE_MAX);
    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, argv[1], len + 1);
    remove_char(buffer, c);
    printf("%s\n", buffer);
    free(buffer);
    buffer = NULL;
    return EXIT_SUCCESS;
}