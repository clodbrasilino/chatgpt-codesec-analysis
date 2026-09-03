#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
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

    int map_s_t[256];
    int map_t_s[256];

    for (size_t i = 0; i < 256; i++) {
        map_s_t[i] = -1;
        map_t_s[i] = -1;
    }

    for (size_t i = 0; i < len_s; i++) {
        unsigned char c1 = (unsigned char)s[i];
        unsigned char c2 = (unsigned char)t[i];

        if (map_s_t[c1] == -1 && map_t_s[c2] == -1) {
            map_s_t[c1] = c2;
            map_t_s[c2] = c1;
        } else if (map_s_t[c1] != c2 || map_t_s[c2] != c1) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const char s1[] = "egg";
    const char t1[] = "add";
    const char s2[] = "foo";
    const char t2[] = "bar";
    const char s3[] = "paper";
    const char t3[] = "title";

    printf("%d\n", isIsomorphic(s1, t1));
    printf("%d\n", isIsomorphic(s2, t2));
    printf("%d\n", isIsomorphic(s3, t3));

    return 0;
}