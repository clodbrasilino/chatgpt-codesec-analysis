#include <stdio.h>
#include <stdbool.h>

#define CHAR_SET 256

bool areIsomorphic(const char *s, size_t s_len, const char *t, size_t t_len) {
    if (s == NULL || t == NULL) {
        return false;
    }

    if (s_len != t_len) {
        return false;
    }

    int map_s[CHAR_SET];
    int map_t[CHAR_SET];

    for (int i = 0; i < CHAR_SET; i++) {
        map_s[i] = -1;
        map_t[i] = -1;
    }

    for (size_t i = 0; i < s_len; i++) {
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
    size_t len1 = 3;
    size_t len2 = 3;
    
    if (areIsomorphic(str1, len1, str2, len2)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    const char *str3 = "foo";
    const char *str4 = "bar";
    size_t len3 = 3;
    size_t len4 = 3;
    
    if (areIsomorphic(str3, len3, str4, len4)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}