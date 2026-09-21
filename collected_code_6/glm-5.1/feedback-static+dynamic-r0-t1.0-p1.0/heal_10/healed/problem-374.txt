#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void permute(char *str, int left, int right) {
    if (left == right) {
        printf("%s\n", str);
        return;
    }

    for (int i = left; i <= right; i++) {
        swap(&str[left], &str[i]);
        permute(str, left + 1, right);
        swap(&str[left], &str[i]);
    }
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t maxlen = 1024;
    size_t len = strnlen(argv[1], maxlen);

    if (len == 0) {
        fprintf(stderr, "Error: Input string cannot be empty.\n");
        return EXIT_FAILURE;
    }

    if (len == maxlen && argv[1][maxlen] != '\0') {
        fprintf(stderr, "Error: Input string exceeds maximum allowed length.\n");
        return EXIT_FAILURE;
    }

    char *buffer = malloc(len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    memcpy(buffer, argv[1], len + 1);

    permute(buffer, 0, (int)len - 1);

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}