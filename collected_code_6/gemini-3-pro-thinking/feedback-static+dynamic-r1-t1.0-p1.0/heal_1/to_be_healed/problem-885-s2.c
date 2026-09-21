#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

bool are_isomorphic(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len_s = strlen(s);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len_t = strlen(t);

    if (len_s != len_t) {
        return false;
    }

    int map_s[256];
    int map_t[256];

    for (int i = 0; i < 256; ++i) {
        map_s[i] = -1;
        map_t[i] = -1;
    }

    for (size_t i = 0; i < len_s; ++i) {
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
    const char *s1 = "egg";
    const char *t1 = "add";
    
    const char *s2 = "foo";
    const char *t2 = "bar";
    
    const char *s3 = "paper";
    const char *t3 = "title";

    if (are_isomorphic(s1, t1)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    if (are_isomorphic(s2, t2)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    if (are_isomorphic(s3, t3)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}