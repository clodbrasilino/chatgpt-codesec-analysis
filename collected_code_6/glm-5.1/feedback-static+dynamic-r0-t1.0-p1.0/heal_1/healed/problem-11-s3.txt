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
        size_t len_first = strnlen(first, (size_t)-1);
        memmove(first, first + 1, len_first);
        return;
    }

    size_t len_last = strnlen(last, (size_t)-1);
    memmove(last, last + 1, len_last);
    
    size_t len_first = strnlen(first, (size_t)-1);
    memmove(first, first + 1, len_first);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <character>\n", argv[0]);
        return 1;
    }

    if (strnlen(argv[2], 2) != 1) {
        fprintf(stderr, "Error: Second argument must be a single character.\n");
        return 1;
    }

    size_t len = strnlen(argv[1], (size_t)-1);
    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1;
    }

    snprintf(buffer, len + 1, "%s", argv[1]);
    char c = argv[2][0];

    remove_first_last(buffer, c);
    printf("%s\n", buffer);

    free(buffer);
    return 0;
}