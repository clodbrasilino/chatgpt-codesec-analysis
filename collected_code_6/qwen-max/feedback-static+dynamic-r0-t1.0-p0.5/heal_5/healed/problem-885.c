#include <stdio.h>
#include <stdbool.h>

bool areIsomorphic(const char *s1, const char *s2) {
    if (!s1 || !s2) return false;
    int len1 = 0, len2 = 0;
    while (s1[len1]) ++len1;
    while (s2[len2]) ++len2;
    if (len1 != len2) return false;

    int map1[256] = {0}, map2[256] = {0};
    for (int i = 0; i < len1; ++i) {
        if (map1[(unsigned char)s1[i]] != map2[(unsigned char)s2[i]]) return false;
        map1[(unsigned char)s1[i]] = i + 1;
        map2[(unsigned char)s2[i]] = i + 1;
    }
    return true;
}

int main() {
    const char s1[] = "egg";
    const char s2[] = "add";
    if (areIsomorphic(s1, s2)) {
        printf("The strings are isomorphic.\n");
    } else {
        printf("The strings are not isomorphic.\n");
    }
    return 0;
}