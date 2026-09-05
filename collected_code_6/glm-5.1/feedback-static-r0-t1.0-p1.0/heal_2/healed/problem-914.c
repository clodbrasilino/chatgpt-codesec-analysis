#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_alternating(const char *str) {
    size_t len;

    if (str == NULL) {
        return 0;
    }

    len = strlen(str);
    if (len < 2) {
        return 0;
    }

    char a = str[0];
    char b = str[1];

    if (a == b) {
        return 0;
    }

    for (size_t i = 2; i < len; i++) {
        if (i % 2 == 0) {
            if (str[i] != a) {
                return 0;
            }
        } else {
            if (str[i] != b) {
                return 0;
            }
        }
    }

    return 1;
}

int main(int argc, char const * const * argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (is_alternating(argv[1])) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return EXIT_SUCCESS;
}