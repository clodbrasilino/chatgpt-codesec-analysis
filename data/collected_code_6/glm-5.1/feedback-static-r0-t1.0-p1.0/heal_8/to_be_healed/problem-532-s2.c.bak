#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool are_permutations(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return false;
    }

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
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