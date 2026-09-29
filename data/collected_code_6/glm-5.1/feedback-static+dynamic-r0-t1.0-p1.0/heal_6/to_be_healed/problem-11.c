#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_first_last(char *str, char c) {
    if (str == NULL) {
        return;
    }

    size_t len = strnlen(str, SIZE_MAX);
    if (len == 0) {
        return;
    }
    if (str[len] != '\0') {
        return;
    }

    char *first = strchr(str, c);
    if (first == NULL) {
        return;
    }

    memmove(first, first + 1, len - (first - str) + 1);

    len = strnlen(str, SIZE_MAX);
    if (len == 0) {
        return;
    }
    if (str[len] != '\0') {
        return;
    }

    char *last = strrchr(str, c);
    if (last == NULL) {
        return;
    }

    memmove(last, last + 1, len - (last - str) + 1);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <char>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strnlen(argv[2], 2) != 1) {
        fprintf(stderr, "Error: Second argument must be a single character.\n");
        return EXIT_FAILURE;
    }

    char c = argv[2][0];
    size_t str_size = strnlen(argv[1], SIZE_MAX) + 1;

    if (argv[1][str_size - 1] != '\0') {
        return EXIT_FAILURE;
    }

    char *str = malloc(str_size);
    if (str == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str, argv[1], str_size);

    remove_first_last(str, c);

    printf("%s\n", str);

    free(str);

    return EXIT_SUCCESS;
}