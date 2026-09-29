#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_chars(const char *src, size_t src_len, char find, char replace) {
    if (src == NULL) {
        return NULL;
    }

    char *result = (char *)malloc(src_len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < src_len; i++) {
        if (src[i] == find) {
            result[i] = replace;
        } else {
            result[i] = src[i];
        }
    }

    result[src_len] = '\0';

    return result;
}

int main(void) {
    const char *original = "hello world";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t original_len = strlen(original);
    char *modified = replace_chars(original, original_len, 'o', 'x');

    if (modified != NULL) {
        printf("%s\n", modified);
        free(modified);
    }

    return 0;
}