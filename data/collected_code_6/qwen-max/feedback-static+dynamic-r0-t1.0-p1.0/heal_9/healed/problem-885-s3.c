#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int areIsomorphic(const char *str1, const char *str2) {
    int map1[256] = {0}, map2[256] = {0};
    size_t m = 0, n = 0;

    while (str1[m] != '\0' && str2[n] != '\0') {
        if (map1[(unsigned char)str1[m]] == 0) map1[(unsigned char)str1[m]] = str2[n];
        if (map2[(unsigned char)str2[n]] == 0) map2[(unsigned char)str2[n]] = str1[m];

        if (map1[(unsigned char)str1[m]] != str2[n] || map2[(unsigned char)str2[n]] != str1[m])
            return 0;

        m++;
        n++;
    }

    if (str1[m] != '\0' || str2[n] != '\0') return 0;

    return 1;
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