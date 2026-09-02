#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool areIsomorphic(char *s1, char *s2) {
    int map1[256], map2[256];
    memset(map1, -1, sizeof(map1));
    memset(map2, -1, sizeof(map2));

    if (strlen(s1) != strlen(s2)) return false;

    for (int i = 0; s1[i] && s2[i]; i++) {
        if (map1[(int)s1[i]] != map2[(int)s2[i]]) return false;

        map1[(int)s1[i]] = i;
        map2[(int)s2[i]] = i;
    }
    return true;
}

int main() {
    char s1[] = "egg";
    char s2[] = "add";

    if (areIsomorphic(s1, s2)) {
        printf("The strings are isomorphic.\n");
    } else {
        printf("The strings are not isomorphic.\n");
    }

    return 0;
}