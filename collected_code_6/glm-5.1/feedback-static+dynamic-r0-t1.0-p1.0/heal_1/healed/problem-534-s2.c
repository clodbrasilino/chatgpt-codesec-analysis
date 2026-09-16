#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *search_string(const char *haystack, const char *needle, size_t *location) {
    if (haystack == NULL || needle == NULL || location == NULL) {
        return NULL;
    }

    size_t needle_len = strlen(needle);
    if (needle_len == 0) {
        *location = 0;
        return (char *)haystack;
    }

    const char *ptr = strstr(haystack, needle);
    if (ptr == NULL) {
        *location = (size_t)-1;
        return NULL;
    }

    *location = (size_t)(ptr - haystack);
    return (char *)ptr;
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