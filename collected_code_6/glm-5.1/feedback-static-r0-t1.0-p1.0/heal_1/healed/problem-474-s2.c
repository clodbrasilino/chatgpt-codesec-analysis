#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_chars(const char *src, char find, char replace) {
    if (src == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (src[len] != '\0') {
        len++;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        if (src[i] == find) {
            result[i] = replace;
        } else {
            result[i] = src[i];
        }
    }

    result[len] = '\0';

    return result;
}

int main(void) {
    const char *original = "hello world";
    char *modified = replace_chars(original, 'o', 'x');

    if (modified != NULL) {
        printf("%s\n", modified);
        free(modified);
    }

    return 0;
}