#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char find_first_repeated(const char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return '\0';
    }

    int *char_count = (int *)calloc(256, sizeof(int));
    if (char_count == NULL) {
        return '\0';
    }

    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        unsigned char c = (unsigned char)str[len];
        if (char_count[c] > 0) {
            free(char_count);
            return str[len];
        }
        char_count[c]++;
        len++;
    }

    free(char_count);
    return '\0';
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char result = find_first_repeated(argv[1], strnlen(argv[1], 1024));
    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("No repeated character found\n");
    }

    return EXIT_SUCCESS;
}