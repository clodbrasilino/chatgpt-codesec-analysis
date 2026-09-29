#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool areIsomorphic(char *s1, char *s2) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(s1) != strlen(s2)) return false;

    int map1[256] = {0}, map2[256] = {0};
    for (size_t i = 0; s1[i] && s2[i]; i++) {
        if (map1[(unsigned char)s1[i]] != map2[(unsigned char)s2[i]]) return false;
        map1[(unsigned char)s1[i]] = map2[(unsigned char)s2[i]] = (int)i + 1;
    }
    return true;
}

int main() {
    char str1[] = "egg";
    char str2[] = "add";
    if (areIsomorphic(str1, str2)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return 0;
}