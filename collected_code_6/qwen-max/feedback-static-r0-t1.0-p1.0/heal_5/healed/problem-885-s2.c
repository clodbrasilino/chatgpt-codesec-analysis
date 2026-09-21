#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

bool areIsomorphic(const char *s1, const char *s2) {
    size_t len1 = 0, len2 = 0;
    while (s1[len1] != '\0') len1++;
    while (s2[len2] != '\0') len2++;
    if (len1 != len2) return false;

    int m1[256] = {0}, m2[256] = {0};
    for (size_t i = 0; i < len1; i++) {
        char c1 = s1[i], c2 = s2[i];
        if (m1[c1] != m2[c2]) return false;
        m1[c1] = i + 1;
        m2[c2] = i + 1;
    }
    return true;
}

int main() {
    const char *str1 = "egg";
    const char *str2 = "add";

    if (areIsomorphic(str1, str2)) {
        printf("The strings are isomorphic.\n");
    } else {
        printf("The strings are not isomorphic.\n");
    }

    return 0;
}