#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count_substrings(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strnlen(str, max_len);
    return len * (len + 1) / 2;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t argv1_len = strnlen(argv[1], 1024);
    if (argv1_len == 1024) {
        fprintf(stderr, "Error: Input string exceeds maximum allowed length\n");
        return EXIT_FAILURE;
    }

    size_t count = count_substrings(argv[1], 1024);
    printf("%zu\n", count);

    return EXIT_SUCCESS;
}