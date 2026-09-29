#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_STRING_LENGTH 4096

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len = 0;

    if (s == NULL) {
        return 0;
    }

    while (len < max_len && s[len] != '\0') {
        len++;
    }

    return len;
}

bool are_isomorphic(const char *str1, const char *str2)
{
    unsigned char map_forward[UCHAR_MAX + 1] = {0};
    bool mapped_forward[UCHAR_MAX + 1] = {false};
    bool mapped_backward[UCHAR_MAX + 1] = {false};
    size_t len1;
    size_t len2;
    size_t i;

    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    len1 = bounded_strlen(str1, MAX_STRING_LENGTH);
    len2 = bounded_strlen(str2, MAX_STRING_LENGTH);

    if (len1 != len2) {
        return false;
    }

    for (i = 0; i < len1; i++) {
        unsigned char c1 = (unsigned char)str1[i];
        unsigned char c2 = (unsigned char)str2[i];

        if (mapped_forward[c1]) {
            if (map_forward[c1] != c2) {
                return false;
            }
        } else {
            if (mapped_backward[c2]) {
                return false;
            }
            map_forward[c1] = c2;
            mapped_forward[c1] = true;
            mapped_backward[c2] = true;
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        const char *program_name = (argc > 0 && argv[0] != NULL) ? argv[0] : "program";
        fprintf(stderr, "Usage: %s <string1> <string2>\n", program_name);
        return EXIT_FAILURE;
    }

    if (are_isomorphic(argv[1], argv[2])) {
        printf("\"%s\" and \"%s\" are isomorphic.\n", argv[1], argv[2]);
    } else {
        printf("\"%s\" and \"%s\" are not isomorphic.\n", argv[1], argv[2]);
    }

    return EXIT_SUCCESS;
}