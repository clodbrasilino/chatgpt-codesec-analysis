#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *search_string(const char *haystack, const char *needle, size_t *location) {
    if (haystack == NULL || needle == NULL || location == NULL) {
        return NULL;
    }

    size_t haystack_len = strnlen(haystack, SIZE_MAX);
    size_t needle_len = strnlen(needle, SIZE_MAX);

    if (needle_len == 0) {
        *location = 0;
        return (char *)haystack;
    }

    if (needle_len > haystack_len) {
        *location = (size_t)-1;
        return NULL;
    }

    for (size_t i = 0; i <= haystack_len - needle_len; i++) {
        size_t j;
        for (j = 0; j < needle_len; j++) {
            if (haystack[i + j] != needle[j]) {
                break;
            }
        }
        if (j == needle_len) {
            *location = i;
            return (char *)&haystack[i];
        }
    }

    *location = (size_t)-1;
    return NULL;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <haystack> <needle>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t loc = 0;
    const char *result = search_string(argv[1], argv[2], &loc);

    if (result != NULL) {
        printf("Found at location: %zu\n", loc);
    } else {
        printf("Not found\n");
    }

    return EXIT_SUCCESS;
}