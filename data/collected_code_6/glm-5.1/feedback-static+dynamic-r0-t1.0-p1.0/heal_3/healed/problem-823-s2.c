#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int starts_with_substring(const char *str, const char *sub) {
    if (str == NULL || sub == NULL) {
        return 0;
    }

    while (*sub != '\0') {
        if (*str == '\0') {
            return 0;
        }
        if (*str != *sub) {
            return 0;
        }
        str++;
        sub++;
    }

    return 1;
}

int main(int argc, char * const * const argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <substring>\n", argv[0]);
        return 1;
    }

    if (starts_with_substring(argv[1], argv[2])) {
        printf("Match\n");
    } else {
        printf("No match\n");
    }

    return 0;
}