#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

size_t shortest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t min_len = SIZE_MAX;
    size_t current_len = 0;

    while (*str != '\0') {
        if (*str == ' ' || *str == '\t' || *str == '\n') {
            if (current_len > 0) {
                if (current_len < min_len) {
                    min_len = current_len;
                }
                current_len = 0;
            }
        } else {
            current_len++;
        }
        str++;
    }

    if (current_len > 0) {
        if (current_len < min_len) {
            min_len = current_len;
        }
    }

    return min_len == SIZE_MAX ? 0 : min_len;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len = shortest_word_length(argv[1]);

    if (len == 0) {
        printf("No words found.\n");
    } else {
        printf("Shortest word length: %zu\n", len);
    }

    return EXIT_SUCCESS;
}