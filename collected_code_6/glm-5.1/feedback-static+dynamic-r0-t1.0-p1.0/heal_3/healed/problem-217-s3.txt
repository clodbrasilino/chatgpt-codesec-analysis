#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char find_first_repeated(const char *str, size_t max_len) {
    if (str == NULL) {
        return '\0';
    }

    size_t len = strnlen(str, max_len);
    unsigned char seen[256] = {0};

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c] == 1) {
            return str[i];
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

    size_t input_len = strlen(argv[1]);
    char result = find_first_repeated(argv[1], input_len + 1);

    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("No repeated character found\n");
    }

    return EXIT_SUCCESS;
}