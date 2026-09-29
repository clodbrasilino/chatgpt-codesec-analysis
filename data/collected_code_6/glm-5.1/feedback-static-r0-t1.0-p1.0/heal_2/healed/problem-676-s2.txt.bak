#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

void remove_non_alphanumeric(const char *src, char *dst, size_t dst_size) {
    if (src == NULL || dst == NULL || dst_size == 0) {
        if (dst != NULL && dst_size > 0) {
            dst[0] = '\0';
        }
        return;
    }

    size_t src_len = strlen(src);
    size_t j = 0;

    for (size_t i = 0; i < src_len; i++) {
        if (j >= dst_size - 1) {
            break;
        }

        if (isalnum((unsigned char)src[i])) {
            dst[j++] = src[i];
        }
    }

    dst[j] = '\0';
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return 1;
    }

    size_t len = strlen(argv[1]);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return 1;
    }

    remove_non_alphanumeric(argv[1], result, len + 1);

    printf("%s\n", result);

    free(result);
    return 0;
}