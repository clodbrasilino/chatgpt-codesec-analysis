#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isIsomorphic(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        return false;
    }

    int map_s[256];
    int map_t[256];

    for (int i = 0; i < 256; i++) {
        map_s[i] = -1;
        map_t[i] = -1;
    }

    size_t i = 0;
    while (s[i] != '\0' && t[i] != '\0') {
        unsigned char c1 = (unsigned char)s[i];
        unsigned char c2 = (unsigned char)t[i];

        if (map_s[c1] == -1 && map_t[c2] == -1) {
            map_s[c1] = c2;
            map_t[c2] = c1;
        } else if (map_s[c1] != c2 || map_t[c2] != c1) {
            return false;
        }
        i++;
    }

    return s[i] == '\0' && t[i] == '\0';
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s[65536];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char t[65536];

    if (argc >= 3) {
        if (isIsomorphic(argv[1], argv[2])) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    } else {
        /* Possible weaknesses found:
         *  scanf() without field width limits can crash with huge input data. [invalidscanf]
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. (risk 4, buffer)
         */
        if (scanf("%s %s", s, t) == 2) {
            if (isIsomorphic(s, t)) {
                printf("True\n");
            } else {
                printf("False\n");
            }
        }
    }

    return 0;
}