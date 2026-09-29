#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t count_substrings(const char *str, size_t max_len) {
    size_t len = strnlen(str, max_len);
    return len * (len + 1) / 2;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len = strlen(argv[1]);
    size_t max_len = 1024;
    size_t bounded_len = len < max_len ? len : max_len;

    size_t count = count_substrings(argv[1], bounded_len);
    printf("%zu\n", count);

    return EXIT_SUCCESS;
}