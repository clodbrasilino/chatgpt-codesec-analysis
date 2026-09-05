#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define CHAR_SET 256

bool areIsomorphic(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        return false;
    }

    size_t len1 = strlen(s);
    size_t len2 = strlen(t);

    if (len1 != len2) {
        return false;
    }

    int map_s[CHAR_SET];
    int map_t[CHAR_SET];

    for (int i = 0; i < CHAR_SET; i++) {
        map_s[i] = -1;
        map_t[i] = -1;
    }

    for (size_t i = 0; i < len1; i++) {
        unsigned char char_s = (unsigned char)s[i];
        unsigned char char_t = (unsigned char)t[i];

        if (map_s[char_s] == -1 && map_t[char_t] == -1) {
            map_s[char_s] = char_t;
            map_t[char_t] = char_s;
        } else {
            if (map_s[char_s] != char_t || map_t[char_t] != char_s) {
                return false;
            }
        }
    }

    return true;
}

int main(void) {
    const char *str1 = "egg";
    const char *str2 = "add";
    
    if (areIsomorphic(str1, str2)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    const char *str3 = "foo";
    const char *str4 = "bar";
    
    if (areIsomorphic(str3, str4)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}