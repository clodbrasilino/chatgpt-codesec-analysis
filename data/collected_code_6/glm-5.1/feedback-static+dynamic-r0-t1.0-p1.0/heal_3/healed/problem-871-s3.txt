#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int are_rotations(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return 0;
    }

    if (s1[0] == '\0' && s2[0] == '\0') {
        return 1;
    }

    size_t len1 = 0;
    while (s1[len1] != '\0') {
        len1++;
    }

    size_t len2 = 0;
    while (s2[len2] != '\0') {
        len2++;
    }

    if (len1 != len2) {
        return 0;
    }

    size_t concat_len = 2 * len1;
    char *concat = (char *)malloc(concat_len + 1);
    if (concat == NULL) {
        exit(EXIT_FAILURE);
    }

    if (concat_len > 0) {
        memcpy(concat, s1, len1);
        memcpy(concat + len1, s1, len1);
    }
    concat[concat_len] = '\0';

    size_t len2_with_null = len2 + 1;
    char *s2_copy = (char *)malloc(len2_with_null);
    if (s2_copy == NULL) {
        free(concat);
        exit(EXIT_FAILURE);
    }
    memcpy(s2_copy, s2, len2_with_null);

    int result = (strstr(concat, s2) != NULL) ? 1 : 0;

    free(concat);
    free(s2_copy);

    return result;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (are_rotations(argv[1], argv[2])) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return EXIT_SUCCESS;
}