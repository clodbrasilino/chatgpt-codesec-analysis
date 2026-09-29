#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_first_last(char *str, char c) {
    if (str == NULL) {
        return;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return;
    }

    char *first = strchr(str, c);
    if (first == NULL) {
        return;
    }

    size_t first_len = strlen(first);
    memmove(first, first + 1, first_len);

    len = strlen(str);
    if (len == 0) {
        return;
    }

    char *last = strrchr(str, c);
    if (last == NULL) {
        return;
    }

    size_t last_len = strlen(last);
    memmove(last, last + 1, last_len);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <char>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strlen(argv[2]) != 1) {
        fprintf(stderr, "Error: Second argument must be a single character.\n");
        return EXIT_FAILURE;
    }

    char c = argv[2][0];
    size_t str_size = strlen(argv[1]) + 1;

    char *str = malloc(str_size);
    if (str == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    memcpy(str, argv[1], str_size);

    remove_first_last(str, c);

    printf("%s\n", str);

    free(str);

    return EXIT_SUCCESS;
}