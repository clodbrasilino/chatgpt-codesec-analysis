#include <stdio.h>
#include <stdlib.h>

void remove_spaces(const char *src, char *dst, size_t len) {
    if (src == NULL || dst == NULL || len == 0) {
        return;
    }

    const char *end = src + len;

    while (*src != '\0' && src < end) {
        if (*src != ' ') {
            if (dst < end - 1) {
                *dst = *src;
                dst++;
            }
        }
        src++;
    }
    *dst = '\0';
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[256];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    remove_spaces(buffer, output, sizeof(output));

    if (fputs(output, stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}