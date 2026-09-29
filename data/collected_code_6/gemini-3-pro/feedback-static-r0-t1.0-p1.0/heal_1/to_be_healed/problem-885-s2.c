#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isIsomorphic(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(s);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(t);

    if (len1 != len2) {
        return false;
    }

    int map_s[256];
    int map_t[256];

    for (int i = 0; i < 256; i++) {
        map_s[i] = -1;
        map_t[i] = -1;
    }

    for (size_t i = 0; i < len1; i++) {
        unsigned char c1 = (unsigned char)s[i];
        unsigned char c2 = (unsigned char)t[i];

        if (map_s[c1] == -1 && map_t[c2] == -1) {
            map_s[c1] = c2;
            map_t[c2] = c1;
        } else if (map_s[c1] != c2 || map_t[c2] != c1) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const char *str1 = "egg";
    const char *str2 = "add";
    
    if (isIsomorphic(str1, str2)) {
        printf("Strings are isomorphic.\n");
    } else {
        printf("Strings are not isomorphic.\n");
    }

    const char *str3 = "foo";
    const char *str4 = "bar";

    if (isIsomorphic(str3, str4)) {
        printf("Strings are isomorphic.\n");
    } else {
        printf("Strings are not isomorphic.\n");
    }

    return 0;
}