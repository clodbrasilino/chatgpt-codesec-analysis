#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_spaces(const char *src, char *dst, size_t dst_size) {
    if (src == NULL || dst == NULL || dst_size == 0) {
        return;
    }

    if (dst_size == 1) {
        dst[0] = '\0';
        return;
    }

    size_t i = 0;
    size_t j = 0;
    size_t max_len = dst_size - 1;

    while (src[i] != '\0') {
        if (src[i] != ' ') {
            if (j < max_len) {
                dst[j++] = src[i];
            } else {
                break;
            }
        }
        i++;
    }
    dst[j] = '\0';
}

int main(void) {
    char *buffer = malloc(256);
    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    char *output = malloc(256);
    if (output == NULL) {
        free(buffer);
        return EXIT_FAILURE;
    }

    if (fgets(buffer, 256, stdin) == NULL) {
        free(buffer);
        free(output);
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    remove_spaces(buffer, output, 256);

    if (fputs(output, stdout) == EOF) {
        free(buffer);
        free(output);
        return EXIT_FAILURE;
    }

    free(buffer);
    free(output);

    return EXIT_SUCCESS;
}