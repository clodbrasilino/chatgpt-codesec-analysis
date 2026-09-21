#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_odd_length(const char *word, size_t max_len) {
    if (word == NULL) {
        return false;
    }
    size_t len = strnlen(word, max_len);
    return len % 2 != 0;
}

int main(int argc, char * const argv[static 2]) {
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