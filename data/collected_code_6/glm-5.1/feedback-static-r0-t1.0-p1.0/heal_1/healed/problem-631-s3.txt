#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_whitespace_underscore(const char *src) {
    if (src == NULL) {
        return NULL;
    }

    size_t len = strnlen(src, SIZE_MAX);
    if (len == 0) {
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t new_len = len + 1;
    char *dest = malloc(new_len);
    if (dest == NULL) {
        return NULL;
    }

    size_t dest_pos = 0;

    for (size_t i = 0; i < len; i++) {
        if (dest_pos + 1 >= new_len) {
            size_t required = new_len * 2;
            if (required <= new_len) {
                required = new_len + 1;
            }
            char *temp = realloc(dest, required);
            if (temp == NULL) {
                free(dest);
                return NULL;
            }
            dest = temp;
            new_len = required;
        }

        if (src[i] == ' ' || src[i] == '_') {
            dest[dest_pos++] = (src[i] == ' ') ? '_' : ' ';
        } else {
            dest[dest_pos++] = src[i];
        }
    }

    if (dest_pos + 1 >= new_len) {
        char *temp = realloc(dest, dest_pos + 1);
        if (temp == NULL) {
            free(dest);
            return NULL;
        }
        dest = temp;
    }

    dest[dest_pos] = '\0';

    char *final_dest = realloc(dest, dest_pos + 1);
    if (final_dest != NULL) {
        return final_dest;
    }

    return dest;
}

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