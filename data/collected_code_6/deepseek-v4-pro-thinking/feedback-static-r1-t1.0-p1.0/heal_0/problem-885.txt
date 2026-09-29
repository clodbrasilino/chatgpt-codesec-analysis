#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isIsomorphic(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        return false;
    }

    size_t len_s = strlen(s);
    size_t len_t = strlen(t);

    if (len_s != len_t) {
        return false;
    }

    unsigned char map_s_t[256] = {0};
    unsigned char map_t_s[256] = {0};

    for (size_t i = 0; i < len_s; i++) {
        unsigned char c1 = (unsigned char)s[i];
        unsigned char c2 = (unsigned char)t[i];

        if (map_s_t[c1] == 0 && map_t_s[c2] == 0) {
            map_s_t[c1] = c2;
            map_t_s[c2] = c1;
        } else if (map_s_t[c1] != c2 || map_t_s[c2] != c1) {
            return false;
        }
    }

    return true;
}

int main(void) {
    printf("%d\n", isIsomorphic("egg", "add"));
    printf("%d\n", isIsomorphic("foo", "bar"));
    printf("%d\n", isIsomorphic("paper", "title"));
    printf("%d\n", isIsomorphic("ab", "aa"));
    printf("%d\n", isIsomorphic("", ""));
    printf("%d\n", isIsomorphic(NULL, "a"));
    return 0;
}