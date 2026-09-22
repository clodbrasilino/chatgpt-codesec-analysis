#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int areIsomorphic(const char *str1, const char *str2) {
    int map1[256] = {0}, map2[256] = {0};
    size_t m = 0, n = 0;

    while (str1[m] != '\0' && str2[n] != '\0') {
        if (!map1[(unsigned char)str1[m]]) map1[(unsigned char)str1[m]] = str2[m];
        if (!map2[(unsigned char)str2[n]]) map2[(unsigned char)str2[n]] = str1[n];

        if (map1[(unsigned char)str1[m]] != str2[m] || map2[(unsigned char)str2[n]] != str1[n])
            return 0;

        m++;
        n++;
    }

    return (str1[m] == '\0' && str2[n] == '\0');
}

int main() {
    const char str1[] = "egg";
    const char str2[] = "add";

    if (areIsomorphic(str1, str2)) {
        printf("The strings are isomorphic.\n");
    } else {
        printf("The strings are not isomorphic.\n");
    }

    return 0;
}