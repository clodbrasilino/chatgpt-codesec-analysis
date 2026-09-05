#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_whitespace_underscore(const char *src) {
    if (src == NULL) {
        return NULL;
    }

    size_t len = strlen(src);
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
    return realloc(dest, dest_pos + 1);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *result = replace_whitespace_underscore(argv[1]);
    if (result == NULL) {
        fprintf(stderr, "Error processing string\n");
        return 1;
    }

    printf("%s\n", result);
    free(result);

    return 0;
}