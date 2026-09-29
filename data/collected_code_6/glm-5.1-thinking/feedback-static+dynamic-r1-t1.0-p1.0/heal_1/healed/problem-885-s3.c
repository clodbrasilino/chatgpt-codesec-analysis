#include <stdio.h>
#include <limits.h>

int isIsomorphic(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        return 0;
    }

    int map_s[UCHAR_MAX + 1];
    int map_t[UCHAR_MAX + 1];

    for (int i = 0; i <= UCHAR_MAX; i++) {
        map_s[i] = -1;
        map_t[i] = -1;
    }

    size_t i = 0;
    while (s[i] != '\0' && t[i] != '\0') {
        unsigned char char_s = (unsigned char)s[i];
        unsigned char char_t = (unsigned char)t[i];

        if (map_s[char_s] == -1 && map_t[char_t] == -1) {
            map_s[char_s] = char_t;
            map_t[char_t] = char_s;
        } else {
            if (map_s[char_s] != char_t || map_t[char_t] != char_s) {
                return 0;
            }
        }
        i++;
    }

    return s[i] == '\0' && t[i] == '\0';
}

int main(void) {
    printf("%d\n", isIsomorphic("egg", "add"));
    printf("%d\n", isIsomorphic("foo", "bar"));
    printf("%d\n", isIsomorphic("paper", "title"));
    printf("%d\n", isIsomorphic("ab", "aa"));
    printf("%d\n", isIsomorphic(NULL, "abc"));
    return 0;
}