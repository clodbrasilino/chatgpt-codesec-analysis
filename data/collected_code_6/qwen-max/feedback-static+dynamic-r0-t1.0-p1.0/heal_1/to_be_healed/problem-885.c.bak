#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool areIsomorphic(char *s1, char *s2) {
    /* Possible weaknesses found:
     *  Variable 'm' is assigned a value that is never used. [unreadVariable]
     */
    int m = 128;
    int map_s1[128] = {0};
    int map_s2[128] = {0};

    if (strlen(s1) != strlen(s2)) return false;

    for (int i = 0; s1[i] && s2[i]; i++) {
        if (map_s1[s1[i]] != map_s2[s2[i]]) return false;
        map_s1[s1[i]] = i + 1;
        map_s2[s2[i]] = i + 1;
    }

    return true;
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