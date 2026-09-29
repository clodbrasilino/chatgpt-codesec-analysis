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

    char *first = strchr(str, c);
    if (first == NULL) {
        return;
    }

    memmove(first, first + 1, strnlen(first, SIZE_MAX));

    len = strnlen(str, SIZE_MAX);
    if (len == 0) {
        return;
    }

    char *last = strrchr(str, c);
    if (last == NULL) {
        return;
    }

    memmove(last, last + 1, strnlen(last, SIZE_MAX));
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <char>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strnlen(argv[2], SIZE_MAX) != 1) {
        fprintf(stderr, "Error: Second argument must be a single character.\n");
        return EXIT_FAILURE;
    }

    size_t len = strnlen(argv[1], SIZE_MAX);
    char *str = malloc(len + 1);
    if (str == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    snprintf(str, len + 1, "%s", argv[1]);
    char c = argv[2][0];

    remove_first_last(str, c);

    printf("%s\n", str);

    free(str);

    return EXIT_SUCCESS;
}