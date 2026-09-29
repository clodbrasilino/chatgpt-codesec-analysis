#include <stdio.h>
#include <stdbool.h>

bool areIsomorphic(char *s1, char *s2) {
    int map_s1[128] = {0};
    int map_s2[128] = {0};
    while (*s1 && *s2) {
        if (map_s1[(unsigned char)*s1] != map_s2[(unsigned char)*s2]) return false;
        map_s1[(unsigned char)*s1] = (int)(s1 - s1 + 1);
        map_s2[(unsigned char)*s2] = (int)(s2 - s2 + 1);
        s1++;
        s2++;
    }
    return *s1 == *s2;
}

int main() {
    char str1[] = "egg";
    char str2[] = "add";
    if (areIsomorphic(str1, str2))
        printf("Yes\n");
    else
        printf("No\n");

    char str3[] = "foo";
    char str4[] = "bar";
    if (areIsomorphic(str3, str4))
        printf("Yes\n");
    else
        printf("No\n");

    return 0;
}