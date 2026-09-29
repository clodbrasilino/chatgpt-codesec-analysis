#include <stdio.h>
#include <string.h>

char *search_string(const char *haystack, const char *needle, size_t *location) {
    size_t haystack_len;
    size_t needle_len;
    size_t i;
    size_t j;

    if (haystack == NULL || needle == NULL || location == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    haystack_len = strlen(haystack);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    needle_len = strlen(needle);

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

    result = search_string(original, pattern, &loc);

    if (result != NULL) {
        printf("Pattern found at location %zu\n", loc);
    } else {
        printf("Pattern not found\n");
    }

    result = search_string(original, "zebra", &loc);

    if (result != NULL) {
        printf("Pattern found at location %zu\n", loc);
    } else {
        printf("Pattern not found\n");
    }

    return 0;
}