#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char find_first_repeated(const char *str, size_t len) {
    unsigned char *seen = calloc(256, sizeof(unsigned char));
    if (seen == NULL) {
        return '\0';
    }

    if (str == NULL) {
        free(seen);
        return '\0';
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c] == 1) {
            free(seen);
            return str[i];
        }
        seen[c] = 1;
    }

    free(seen);
    return '\0';
}

int main(int argc, char const * const *argv) {
    char result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(argv[1]);
    result = find_first_repeated(argv[1], len);

    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("No repeated character found\n");
    }

    return EXIT_SUCCESS;
}