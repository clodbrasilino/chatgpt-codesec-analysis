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
        memmove(first, first + 1, strlen(first));
        return;
    }

    memmove(last, last + 1, strlen(last));
    memmove(first, first + 1, strlen(first));
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <character>\n", argv[0]);
        return 1;
    }

    if (strlen(argv[2]) != 1) {
        fprintf(stderr, "Error: Second argument must be a single character.\n");
        return 1;
    }

    size_t len = strlen(argv[1]);
    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1;
    }

    strcpy(buffer, argv[1]);
    char c = argv[2][0];

    remove_first_last(buffer, c);
    printf("%s\n", buffer);

    free(buffer);
    return 0;
}