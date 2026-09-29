#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char find_first_repeated(const char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return '\0';
    }

    unsigned char seen[UCHAR_MAX + 1];
    memset(seen, 0, sizeof(seen));

    for (size_t i = 0; i < max_len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (c == '\0') {
            break;
        }
        if (seen[c] == 1) {
            return (char)c;
        }
        seen[c] = 1;
    }

    return '\0';
}

int main(int argc, char const * const * argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char result = find_first_repeated(argv[1], strnlen(argv[1], 4096));

    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("No repeated character found\n");
    }

    return EXIT_SUCCESS;
}