#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int ends_with_alphanumeric(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return 0;
    }

    char last = str[len - 1];
    if (isalnum((unsigned char)last)) {
        return 1;
    }

    return 0;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len = strnlen(argv[1], 1024);
    if (ends_with_alphanumeric(argv[1], len)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return EXIT_SUCCESS;
}