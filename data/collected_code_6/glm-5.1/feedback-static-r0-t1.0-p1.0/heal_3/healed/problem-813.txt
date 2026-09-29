#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t string_length(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }

    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }

    return len;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len = string_length(argv[1], strnlen(argv[1], 1024));
    printf("%zu\n", len);

    return EXIT_SUCCESS;
}