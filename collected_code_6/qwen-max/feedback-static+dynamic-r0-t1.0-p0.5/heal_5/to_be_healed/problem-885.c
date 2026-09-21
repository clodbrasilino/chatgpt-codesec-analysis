#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool areIsomorphic(const char *s1, const char *s2) {
    if (!s1 || !s2) return false;
    if (s1[0] == '\0' || s2[0] == '\0') return false;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(s1) != strlen(s2)) return false;

    int map1[256] = {0}, map2[256] = {0};
    for (int i = 0; s1[i] && s2[i]; ++i) {
        if (map1[(unsigned char)s1[i]] != map2[(unsigned char)s2[i]]) return false;
        map1[(unsigned char)s1[i]] = i + 1;
        map2[(unsigned char)s2[i]] = i + 1;
    }
    return true;
}

int main() {
    const char s1[] = "egg";
    const char s2[] = "add";
    if (areIsomorphic(s1, s2)) {
        printf("The strings are isomorphic.\n");
    } else {
        printf("The strings are not isomorphic.\n");
    }
    return 0;
}