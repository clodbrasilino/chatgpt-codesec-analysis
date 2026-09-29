#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min_swaps(const char *s1, const char *s2) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(s2);

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
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", argv[0]);
        return 1;
    }

    int result = min_swaps(argv[1], argv[2]);

    if (result == -1) {
        printf("Impossible to make strings equal\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}