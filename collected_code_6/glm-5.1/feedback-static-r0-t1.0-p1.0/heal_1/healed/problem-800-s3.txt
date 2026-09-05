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

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *buffer = malloc(strlen(argv[1]) + 1);
    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    strcpy(buffer, argv[1]);

    remove_whitespace(buffer);

    printf("%s\n", buffer);

    free(buffer);
    return EXIT_SUCCESS;
}