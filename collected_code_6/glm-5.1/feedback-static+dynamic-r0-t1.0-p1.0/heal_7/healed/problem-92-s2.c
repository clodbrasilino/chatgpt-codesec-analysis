#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int is_undulating(const char *s) {
    if (s == NULL) {
        return 0;
    }

    size_t len = strnlen(s, 256);

    if (len < 3) {
        return 0;
    }

    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)s[i])) {
            return 0;
        }
    }

    if (s[0] == s[1]) {
        return 0;
    }

    for (size_t i = 2; i < len; i++) {
        if (s[i] != s[i - 2]) {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strnlen(argv[1], 256) >= 256) {
        fprintf(stderr, "Input exceeds maximum allowed length\n");
        return EXIT_FAILURE;
    }

    if (is_undulating(argv[1])) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return EXIT_SUCCESS;
}