#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int check_vowels(const char *str, size_t len) {
    if (str == NULL) {
        return 0;
    }

    int has_a = 0, has_e = 0, has_i = 0, has_o = 0, has_u = 0;

    for (size_t i = 0; i < len; i++) {
        char lower = tolower((unsigned char)str[i]);
        switch (lower) {
            case 'a': has_a = 1; break;
            case 'e': has_e = 1; break;
            case 'i': has_i = 1; break;
            case 'o': has_o = 1; break;
            case 'u': has_u = 1; break;
            default: break;
        }
    }

    return has_a && has_e && has_i && has_o && has_u;
}

int main(int argc, char * const * argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t max_len = 256;
    size_t len = strnlen(argv[1], max_len);

    if (len >= max_len) {
        fprintf(stderr, "Error: String exceeds maximum allowed length or is not null-terminated\n");
        return EXIT_FAILURE;
    }

    if (check_vowels(argv[1], len)) {
        printf("Accepted\n");
    } else {
        printf("Rejected\n");
    }

    return EXIT_SUCCESS;
}