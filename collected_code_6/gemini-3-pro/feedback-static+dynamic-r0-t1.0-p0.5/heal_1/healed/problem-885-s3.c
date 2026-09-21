#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool areIsomorphic(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    int map1[256];
    int map2[256];

    for (int i = 0; i < 256; i++) {
        map1[i] = -1;
        map2[i] = -1;
    }

    size_t i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        unsigned char c1 = (unsigned char)str1[i];
        unsigned char c2 = (unsigned char)str2[i];

        if (map1[c1] == -1 && map2[c2] == -1) {
            map1[c1] = c2;
            map2[c2] = c1;
        } else if (map1[c1] != c2 || map2[c2] != c1) {
            return false;
        }
        i++;
    }

    if (str1[i] != '\0' || str2[i] != '\0') {
        return false;
    }

    return true;
}

int main(void) {
    const char *str1 = "egg";
    const char *str2 = "add";

    if (areIsomorphic(str1, str2)) {
        printf("The strings are isomorphic.\n");
    } else {
        printf("The strings are not isomorphic.\n");
    }

    const char *str3 = "foo";
    const char *str4 = "bar";

    if (areIsomorphic(str3, str4)) {
        printf("The strings are isomorphic.\n");
    } else {
        printf("The strings are not isomorphic.\n");
    }

    return 0;
}