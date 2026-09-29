#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_first_last(char *str, char c) {
    if (str == NULL || *str == '\0') {
        return;
    }

    char *first = strchr(str, c);
    if (first == NULL) {
        return;
    }

    char *last = strrchr(str, c);

    if (first == last) {
        size_t len = strnlen(first, (size_t)-1);
        memmove(first, first + 1, len);
        return;
    }

    size_t last_len = strnlen(last, (size_t)-1);
    memmove(last, last + 1, last_len);

    size_t first_len = strnlen(first, (size_t)-1);
    memmove(first, first + 1, first_len);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <character>\n", argv[0]);
        return 1;
    }

    if (argv[2][0] == '\0' || argv[2][1] != '\0') {
        fprintf(stderr, "Error: Second argument must be a single character.\n");
        return 1;
    }

    size_t len = strnlen(argv[1], 1024 * 1024);
    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1;
    }

    memcpy(buffer, argv[1], len + 1);
    buffer[len] = '\0';
    char c = argv[2][0];

    remove_first_last(buffer, c);
    printf("%s\n", buffer);

    free(buffer);
    return 0;
}