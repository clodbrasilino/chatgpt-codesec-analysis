#include <stdio.h>
#include <string.h>

int areIsomorphic(const char *s, size_t s_len, const char *t, size_t t_len) {
    if (s == NULL || t == NULL) {
        return 0;
    }

    if (s_len != t_len) {
        return 0;
    }

    int s_to_t[256];
    int t_to_s[256];

    memset(s_to_t, -1, sizeof(s_to_t));
    memset(t_to_s, -1, sizeof(t_to_s));

    for (size_t i = 0; i < s_len; i++) {
        unsigned char c1 = (unsigned char)s[i];
        unsigned char c2 = (unsigned char)t[i];

        if (s_to_t[c1] == -1 && t_to_s[c2] == -1) {
            s_to_t[c1] = c2;
            t_to_s[c2] = c1;
        } else if (s_to_t[c1] != c2 || t_to_s[c2] != c1) {
            return 0;
        }
    }

    return 1;
}

int main() {
    const char str1[] = "egg";
    const char str2[] = "add";
    const char str3[] = "foo";
    const char str4[] = "bar";
    const char str5[] = "paper";
    const char str6[] = "title";

    printf("%d\n", areIsomorphic(str1, sizeof(str1) - 1, str2, sizeof(str2) - 1));
    printf("%d\n", areIsomorphic(str3, sizeof(str3) - 1, str4, sizeof(str4) - 1));
    printf("%d\n", areIsomorphic(str5, sizeof(str5) - 1, str6, sizeof(str6) - 1));
    printf("%d\n", areIsomorphic(NULL, 0, str1, sizeof(str1) - 1));

    return 0;
}