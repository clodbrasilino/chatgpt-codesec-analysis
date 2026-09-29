#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

size_t remove_whitespace(char *str) {
    if (str == NULL) {
        return 0;
    }

    char *dst = str;
    char *src = str;
    size_t count = 0;

    while (*src != '\0') {
        if (!isspace((unsigned char)*src)) {
            *dst = *src;
            dst++;
            count++;
        }
        src++;
    }

    *dst = '\0';
    return count;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len = strnlen(argv[1], SIZE_MAX);
    char *buffer = malloc(len + 1);
    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    snprintf(buffer, len + 1, "%s", argv[1]);

    remove_whitespace(buffer);

    printf("%s\n", buffer);

    free(buffer);
    return EXIT_SUCCESS;
}