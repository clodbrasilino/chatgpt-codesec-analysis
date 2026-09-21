#include <stdio.h>
#include <string.h>

int areIsomorphic(const char *s, size_t len_s, const char *t, size_t len_t) {
    if (s == NULL || t == NULL) {
        return 0;
    }
    if (len_s != len_t) {
        return 0;
    }
    unsigned char map_st[256] = {0};
    unsigned char map_ts[256] = {0};
    for (size_t i = 0; i < len_s; i++) {
        unsigned char c_s = (unsigned char)s[i];
        unsigned char c_t = (unsigned char)t[i];
        if (map_st[c_s] == 0 && map_ts[c_t] == 0) {
            map_st[c_s] = c_t;
            map_ts[c_t] = c_s;
        } else {
            if (map_st[c_s] != c_t || map_ts[c_t] != c_s) {
                return 0;
            }
        }
    }
    return 1;
}

int main(void) {
    const char *str1 = "egg";
    const char *str2 = "add";
    const char *str3 = "foo";
    const char *str4 = "bar";
    const char *str5 = "paper";
    const char *str6 = "title";
    const char *str7 = NULL;
    const char *str8 = "abc";

    printf("%d\n", areIsomorphic(str1, str1 ? strlen(str1) : 0, str2, str2 ? strlen(str2) : 0));
    printf("%d\n", areIsomorphic(str3, str3 ? strlen(str3) : 0, str4, str4 ? strlen(str4) : 0));
    printf("%d\n", areIsomorphic(str5, str5 ? strlen(str5) : 0, str6, str6 ? strlen(str6) : 0));
    printf("%d\n", areIsomorphic(str7, 0, str8, str8 ? strlen(str8) : 0));

    return 0;
}