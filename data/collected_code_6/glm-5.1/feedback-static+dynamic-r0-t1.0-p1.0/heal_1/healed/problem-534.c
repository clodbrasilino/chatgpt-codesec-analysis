#include <stdio.h>
#include <string.h>

char *search_string(const char *haystack, const char *needle, size_t max_len, size_t *location) {
    size_t haystack_len;
    size_t needle_len;
    size_t i;
    size_t j;

    if (haystack == NULL || needle == NULL || location == NULL) {
        return NULL;
    }

    haystack_len = strnlen(haystack, max_len);
    needle_len = strnlen(needle, max_len);

    if (needle_len == 0) {
        *location = 0;
        return (char *)haystack;
    }

    if (needle_len > haystack_len) {
        return NULL;
    }

    for (i = 0; i <= haystack_len - needle_len; i++) {
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

    return NULL;
}

int main(void) {
    const char *original = "The quick brown fox jumps over the lazy dog";
    const char *pattern = "brown fox";
    size_t loc;
    char *result;
    size_t buffer_max = 256;

    result = search_string(original, pattern, buffer_max, &loc);

    if (result != NULL) {
        printf("Pattern found at location %zu\n", loc);
    } else {
        printf("Pattern not found\n");
    }

    result = search_string(original, "zebra", buffer_max, &loc);

    if (result != NULL) {
        printf("Pattern found at location %zu\n", loc);
    } else {
        printf("Pattern not found\n");
    }

    return 0;
}