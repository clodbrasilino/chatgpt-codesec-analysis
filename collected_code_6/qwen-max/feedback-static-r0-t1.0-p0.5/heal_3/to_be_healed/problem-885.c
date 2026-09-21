#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool areIsomorphic(const char *s1, const char *s2) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t m = strlen(s1), n = strlen(s2);
    if (m != n) return false;

    int map1[256] = {0}, map2[256] = {0};
    for (size_t i = 0; i < m; ++i) {
        if (map1[(unsigned char)s1[i]] != map2[(unsigned char)s2[i]]) return false;
        map1[(unsigned char)s1[i]] = i + 1;
        map2[(unsigned char)s2[i]] = i + 1;
    }
    return true;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 's1' can be declared as const array [constVariable]
     */
    char s1[] = "egg";
    /* Possible weaknesses found:
     *  Variable 's2' can be declared as const array [constVariable]
     */
    char s2[] = "add";
    if (areIsomorphic(s1, s2)) {
        printf("The strings are isomorphic.\n");
    } else {
        printf("The strings are not isomorphic.\n");
    }
    return 0;
}