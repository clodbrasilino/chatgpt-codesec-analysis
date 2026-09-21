#include <stdio.h>
#include <stdbool.h>

bool is_odd_length(const char *word, size_t max_len) {
    if (word == NULL) {
        return false;
    }
    size_t len = 0;
    while (len < max_len && word[len] != '\0') {
        len++;
    }
    if (len == max_len && word[len] != '\0') {
        return false;
    }
    return len % 2 != 0;
}

int main(int argc, char * const * const argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <word>\n", argv[0]);
        return 1;
    }

    if (is_odd_length(argv[1], 4096)) {
        printf("odd\n");
    } else {
        printf("even\n");
    }

    return 0;
}