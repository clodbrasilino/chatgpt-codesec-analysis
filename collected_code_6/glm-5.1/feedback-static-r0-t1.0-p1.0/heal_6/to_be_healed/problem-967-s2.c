#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int check_vowels(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int has_a = 0, has_e = 0, has_i = 0, has_o = 0, has_u = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(argv[1]);
    if (len >= 256) {
        fprintf(stderr, "Error: String exceeds maximum allowed length\n");
        return EXIT_FAILURE;
    }

    if (check_vowels(argv[1])) {
        printf("Accepted\n");
    } else {
        printf("Rejected\n");
    }

    return EXIT_SUCCESS;
}