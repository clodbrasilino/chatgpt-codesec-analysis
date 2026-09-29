#include <stdio.h>
#include <stdbool.h>

bool isIsomorphic(const char* str1, const char* str2) {
    int map1[256] = {0};
    int map2[256] = {0};

    for (int i = 0; str1[i] != '\0' && str2[i] != '\0'; i++) {
        if (map1[(unsigned char)str1[i]] == 0 && map2[(unsigned char)str2[i]] == 0) {
            map1[(unsigned char)str1[i]] = str2[i];
            map2[(unsigned char)str2[i]] = str1[i];
        } else if (map1[(unsigned char)str1[i]] != str2[i] || map2[(unsigned char)str2[i]] != str1[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    char str1[] = "egg";
    char str2[] = "add";

    if (isIsomorphic(str1, str2)) {
        printf("The strings are isomorphic.\n");
    } else {
        printf("The strings are not isomorphic.\n");
    }

    return 0;
}