#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void move_numbers(const char *src, char *dst, size_t dst_size) {
    if (src == NULL || dst == NULL || dst_size == 0) {
        return;
    }

    size_t dst_idx = 0;
    for (size_t i = 0; src[i] != '\0'; i++) {
        if (isdigit((unsigned char)src[i])) {
            if (dst_idx < dst_size - 1) {
                dst[dst_idx++] = src[i];
            } else {
                break;
            }
        }
    }
    dst[dst_idx] = '\0';
}

int main(void) {
    const char *input = "A1B2C3D4E5";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t dst_size = strlen(input) + 1;
    char *dst = malloc(dst_size);

    if (dst == NULL) {
        return EXIT_FAILURE;
    }

    move_numbers(input, dst, dst_size);
    printf("%s\n", dst);

    free(dst);
    dst = NULL;

    return EXIT_SUCCESS;
}