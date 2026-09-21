#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char *replace_whitespace_underscore(const char *src) {
    if (src == NULL) {
        return NULL;
    }

    size_t len = safe_strlen(src, 1024 * 1024);
    char *dest = malloc(len + 1);
    if (dest == NULL) {
        return NULL;
    }

    size_t dest_pos = 0;

    for (size_t i = 0; i < len; i++) {
        if (src[i] == ' ') {
            dest[dest_pos++] = '_';
        } else if (src[i] == '_') {
            dest[dest_pos++] = ' ';
        } else {
            dest[dest_pos++] = src[i];
        }
    }

    dest[dest_pos] = '\0';

    return dest;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    (void)argv;

    char *result = replace_whitespace_underscore(argv[1]);
    if (result == NULL) {
        fprintf(stderr, "Error processing string\n");
        return 1;
    }

    printf("%s\n", result);
    free(result);

    return 0;
}