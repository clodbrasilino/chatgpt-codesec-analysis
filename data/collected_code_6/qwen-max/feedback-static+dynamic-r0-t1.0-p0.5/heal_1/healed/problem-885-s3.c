#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool areIsomorphic(char *s1, char *s2) {
    int map1[256], map2[256];
    memset(map1, -1, sizeof(map1));
    memset(map2, -1, sizeof(map2));

    while (*s1 && *s2) {
        if (map1[(unsigned char)*s1] != map2[(unsigned char)*s2]) return false;
        map1[(unsigned char)*s1] = map2[(unsigned char)*s2] = *s1;
        s1++;
        s2++;
    }

    return *s1 == *s2;
}

int main() {
    char str1[] = "egg";
    char str2[] = "add";

    if (areIsomorphic(str1, str2)) {
        printf("The strings are isomorphic.\n");
    } else {
        printf("The strings are not isomorphic.\n");
    }

    return 0;
}