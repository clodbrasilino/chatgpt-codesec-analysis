#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHAR_SET 256

int are_isomorphic(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return 0;
    }

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    if (len1 != len2) {
        return 0;
    }

    int map_s1[CHAR_SET];
    int map_s2[CHAR_SET];

    for (int i = 0; i < CHAR_SET; i++) {
        map_s1[i] = -1;
        map_s2[i] = -1;
    }

    for (size_t i = 0; i < len1; i++) {
        unsigned char c1 = (unsigned char)s1[i];
        unsigned char c2 = (unsigned char)s2[i];

        if (map_s1[c1] == -1 && map_s2[c2] == -1) {
            map_s1[c1] = c2;
            map_s2[c2] = c1;
        } else if (map_s1[c1] != c2 || map_s2[c2] != c1) {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char const * const argv[const]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (are_isomorphic(argv[1], argv[2])) {
        printf("Isomorphic\n");
    } else {
        printf("Not Isomorphic\n");
    }

    return EXIT_SUCCESS;
}