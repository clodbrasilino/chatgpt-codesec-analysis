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
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t count = count_substrings(argv[1], 1024);
    printf("%zu\n", count);

    return EXIT_SUCCESS;
}