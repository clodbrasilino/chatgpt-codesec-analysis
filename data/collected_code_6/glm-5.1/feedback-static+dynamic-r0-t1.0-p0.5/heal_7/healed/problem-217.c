#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char find_first_repeated(const char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return '\0';
    }

    unsigned char char_set[UCHAR_MAX + 1] = {0};

    size_t i = 0;
    while (i < max_len && str[i] != '\0') {
        unsigned char c = (unsigned char)str[i];
        if (char_set[c] == 1) {
            return str[i];
        }
        char_set[c] = 1;
        i++;
    }

    return '\0';
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char result = find_first_repeated(argv[1], 4096);

    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("No repeated character found\n");
    }

    return EXIT_SUCCESS;
}