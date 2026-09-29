#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

bool are_permutations(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return false;
    }

    size_t len1 = strnlen(s1, SIZE_MAX);
    size_t len2 = strnlen(s2, SIZE_MAX);

    if (len1 != len2) {
        return false;
    }

    unsigned int count[256] = {0};

    for (size_t i = 0; i < len1; i++) {
        count[(unsigned char)s1[i]]++;
        count[(unsigned char)s2[i]]--;
    }

    for (int i = 0; i < 256; i++) {
        if (count[i] != 0) {
            return false;
        }
    }

    return true;
}

int main(int argc, char const * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", argv[0]);
        return 1;
    }

    bool result = are_permutations(argv[1], argv[2]);

    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}