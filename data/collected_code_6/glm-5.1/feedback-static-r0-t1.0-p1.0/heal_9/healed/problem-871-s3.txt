#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int are_rotations(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return 0;
    }

    size_t len1 = strnlen(s1, SIZE_MAX);
    size_t len2 = strnlen(s2, SIZE_MAX);

    if (len1 != len2) {
        return 0;
    }

    if (len1 == 0) {
        return 1;
    }

    size_t concat_len = 2 * len1;
    char *concat = (char *)malloc(concat_len + 1);
    if (concat == NULL) {
        exit(EXIT_FAILURE);
    }

    memcpy_s(concat, concat_len + 1, s1, len1);
    memcpy_s(concat + len1, len1 + 1, s1, len1);
    concat[concat_len] = '\0';

    int result = (strstr(concat, s2) != NULL) ? 1 : 0;

    free(concat);

    return result;
}

int main(int argc, char const * const * argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (are_rotations(argv[1], argv[2])) {
        printf("Strings are rotations of each other.\n");
    } else {
        printf("Strings are not rotations of each other.\n");
    }

    return EXIT_SUCCESS;
}