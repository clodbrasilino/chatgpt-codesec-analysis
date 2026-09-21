#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_spaces(char *str, size_t len) {
    if (str == NULL) {
        return;
    }

    char *dst = str;
    const char *src = str;
    const char *end = str + len;

    while (src < end && *src != '\0') {
        if (*src != ' ') {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
}

int main(void) {
    size_t buffer_size = 256;
    char *buffer = malloc(buffer_size * sizeof(char));

    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(buffer, buffer_size, stdin) == NULL) {
        free(buffer);
        return EXIT_FAILURE;
    }

    remove_spaces(buffer, buffer_size);

    if (fputs(buffer, stdout) == EOF) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}