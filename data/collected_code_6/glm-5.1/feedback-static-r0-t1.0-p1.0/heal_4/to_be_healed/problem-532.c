#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int are_permutations(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(s2);

    if (len1 != len2) {
        return 0;
    }

    size_t counts[256] = {0};

    for (size_t i = 0; i < len1; i++) {
        unsigned char c1 = (unsigned char)s1[i];
        unsigned char c2 = (unsigned char)s2[i];
        counts[c1]++;
        counts[c2]--;
    }

    for (size_t i = 0; i < 256; i++) {
        if (counts[i] != 0) {
            return 0;
        }
    }

    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = are_permutations(argv[1], argv[2]);
    
    printf("%d\n", result);

    return EXIT_SUCCESS;
}