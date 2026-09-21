#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t count_substrings(const char *str, size_t max_len) {
    const char *end = memchr(str, '\0', max_len);
    if (end == NULL) {
        return 0;
    }
    size_t len = (size_t)(end - str);
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

    size_t arg_len = strnlen(argv[1], 1024);
    if (arg_len == 1024) {
        fprintf(stderr, "Error: Input string exceeds maximum allowed length\n");
        return EXIT_FAILURE;
    }

    size_t count = count_substrings(argv[1], 1024);
    printf("%zu\n", count);

    return EXIT_SUCCESS;
}