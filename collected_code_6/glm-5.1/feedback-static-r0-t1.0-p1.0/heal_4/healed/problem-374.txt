#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void permute(char *str, size_t left, size_t right) {
    if (left == right) {
        printf("%s\n", str);
        return;
    }

    for (size_t i = left; i <= right; i++) {
        swap(&str[left], &str[i]);
        permute(str, left + 1, right);
        swap(&str[left], &str[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t max_len = 1024 * 1024;
    size_t len = strnlen(argv[1], max_len);

    if (len == 0 || len == max_len) {
        fprintf(stderr, "Error: Input string cannot be empty or exceed maximum length.\n");
        return EXIT_FAILURE;
    }

    char *buffer = malloc(len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    memcpy(buffer, argv[1], len + 1);
    buffer[len] = '\0';

    permute(buffer, 0, len - 1);

    free(buffer);

    return EXIT_SUCCESS;
}