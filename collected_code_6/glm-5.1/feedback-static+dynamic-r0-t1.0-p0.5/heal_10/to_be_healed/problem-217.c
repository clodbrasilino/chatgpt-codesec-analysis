#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char find_first_repeated(const char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return '\0';
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char char_set[UCHAR_MAX + 1] = {0};

    for (size_t i = 0; i < max_len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (c == '\0') {
            break;
        }
        if (char_set[c] == 1) {
            return str[i];
        }
        char_set[c] = 1;
    }

    return '\0';
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t effective_len = strnlen(argv[1], 4096);
    
    char result = find_first_repeated(argv[1], effective_len);

    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("No repeated character found\n");
    }

    return EXIT_SUCCESS;
}