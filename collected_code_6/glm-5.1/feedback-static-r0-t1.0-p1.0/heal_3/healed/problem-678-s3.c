#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_spaces(const char *src, char *dst, size_t dst_size) {
    if (src == NULL || dst == NULL || dst_size == 0) {
        return;
    }

    size_t i = 0;
    size_t j = 0;

    while (src[i] != '\0') {
        if (src[i] != ' ') {
            if (j < dst_size - 1) {
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
    char buffer[256];
    char output[256];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    remove_spaces(buffer, output, sizeof(output));

    if (fputs(output, stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}