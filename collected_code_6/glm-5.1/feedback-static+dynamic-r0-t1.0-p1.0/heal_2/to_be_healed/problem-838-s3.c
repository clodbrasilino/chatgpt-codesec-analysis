#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min_swaps(const char *s1, const char *s2, size_t max_len) {
    size_t len1 = strnlen(s1, max_len);
    size_t len2 = strnlen(s2, max_len);

    if (len1 != len2) {
        return -1;
    }

    size_t len = len1;
    size_t xy = 0;
    size_t yx = 0;

    for (size_t i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '0') {
                xy++;
            } else {
                yx++;
            }
        }
    }

    if ((xy + yx) % 2 != 0) {
        return -1;
    }

    return (xy / 2) + (yx / 2) + (xy % 2) + (yx % 2);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", argv[0]);
        return 1;
    }

    int result = min_swaps(argv[1], argv[2], 4096);

    if (result == -1) {
        printf("Impossible to make strings equal\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}