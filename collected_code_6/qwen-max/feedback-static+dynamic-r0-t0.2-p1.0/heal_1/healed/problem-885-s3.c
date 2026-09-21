#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool areIsomorphic(const char *s1, const char *s2) {
    int map1[256], map2[256];
    for (int i = 0; i < 256; i++) {
        map1[i] = -1;
        map2[i] = -1;
    }

    while (*s1 && *s2) {
        if (map1[(int)*s1] != map2[(int)*s2]) return false;

        map1[(int)*s1] = (int)*s1;
        map2[(int)*s2] = (int)*s1;

        s1++;
        s2++;
    }

    return *s1 == *s2;
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