#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *replace_chars(const char *src, char find, char replace) {
    if (src == NULL) {
        return NULL;
    }

    size_t len = strlen(src);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        result[i] = (src[i] == find) ? replace : src[i];
    }
    result[len] = '\0';

    return result;
}

int main(void) {
    const char *original = "hello world";
    char *modified = replace_chars(original, 'o', '0');

    if (modified == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", modified);
    free(modified);

    return EXIT_SUCCESS;
}