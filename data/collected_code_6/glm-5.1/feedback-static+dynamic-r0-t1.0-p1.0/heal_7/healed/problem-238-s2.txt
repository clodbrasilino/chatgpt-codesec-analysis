#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t count_substrings(const char *str, size_t max_len) {
    size_t len = strnlen(str, max_len);
    return len * (len + 1) / 2;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t max_len = 1024;
    size_t argv1_len = strnlen(argv[1], max_len);
    if (argv1_len == max_len) {
        fprintf(stderr, "Error: Input string exceeds maximum allowed length of %zu\n", max_len);
        return EXIT_FAILURE;
    }

    size_t count = count_substrings(argv[1], max_len);
    printf("%zu\n", count);

    return EXIT_SUCCESS;
}