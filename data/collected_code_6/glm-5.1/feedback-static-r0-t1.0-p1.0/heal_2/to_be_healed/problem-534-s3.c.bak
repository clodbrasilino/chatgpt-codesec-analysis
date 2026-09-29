#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *find_string(const char *haystack, const char *needle, size_t *location) {
    if (haystack == NULL || needle == NULL || location == NULL) {
        return NULL;
    }

    size_t needle_len = strlen(needle);
    if (needle_len == 0) {
        *location = 0;
        return (char *)haystack;
    }

    size_t haystack_len = strlen(haystack);
    if (needle_len > haystack_len) {
        return NULL;
    }

    for (size_t i = 0; i <= haystack_len - needle_len; i++) {
        if (memcmp(haystack + i, needle, needle_len) == 0) {
            *location = i;
            return (char *)haystack + i;
        }
    }

    return NULL;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <haystack> <needle>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t location = 0;
    const char *result = find_string(argv[1], argv[2], &location);

    if (result != NULL) {
        printf("Pattern found at location: %zu\n", location);
    } else {
        printf("Pattern not found\n");
    }

    return EXIT_SUCCESS;
}