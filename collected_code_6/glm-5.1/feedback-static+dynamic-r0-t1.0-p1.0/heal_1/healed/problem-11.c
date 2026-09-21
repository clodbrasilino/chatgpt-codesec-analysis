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

    size_t first_len = strnlen(first, SIZE_MAX);
    memmove(first, first + 1, first_len);

    len = strnlen(str, SIZE_MAX);
    if (len == 0) {
        return;
    }

    char *last = strrchr(str, c);
    if (last == NULL) {
        return;
    }

    size_t last_len = strnlen(last, SIZE_MAX);
    memmove(last, last + 1, last_len);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <char>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t arg_len = strnlen(argv[2], SIZE_MAX);
    if (arg_len != 1) {
        fprintf(stderr, "Error: Second argument must be a single character.\n");
        return EXIT_FAILURE;
    }

    char c = argv[2][0];
    size_t str_size = strnlen(argv[1], SIZE_MAX) + 1;

    char *str = (char *)malloc(str_size * sizeof(char));
    if (str == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    memcpy(str, argv[1], str_size);
    str[str_size - 1] = '\0';

    remove_first_last(str, c);

    printf("%s\n", str);

    free(str);

    return EXIT_SUCCESS;
}