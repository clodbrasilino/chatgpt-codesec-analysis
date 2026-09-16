#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool are_isomorphic(const char *s1, const char *s2)
{
    if (s1 == NULL || s2 == NULL) {
        return false;
    }

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    if (len1 != len2) {
        return false;
    }

    int map_forward[256];
    int map_backward[256];

    for (int i = 0; i < 256; i++) {
        map_forward[i] = -1;
        map_backward[i] = -1;
    }

    for (size_t i = 0; i < len1; i++) {
        unsigned char c1 = (unsigned char)s1[i];
        unsigned char c2 = (unsigned char)s2[i];

        if (map_forward[c1] == -1 && map_backward[c2] == -1) {
            map_forward[c1] = (int)c2;
            map_backward[c2] = (int)c1;
        } else if (map_forward[c1] != (int)c2 || map_backward[c2] != (int)c1) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const char *str1 = "egg";
    const char *str2 = "add";
    const char *str3 = "foo";
    const char *str4 = "bar";

    if (are_isomorphic(str1, str2)) {
        printf("\"%s\" and \"%s\" are isomorphic\n", str1, str2);
    } else {
        printf("\"%s\" and \"%s\" are not isomorphic\n", str1, str2);
    }

    if (are_isomorphic(str3, str4)) {
        printf("\"%s\" and \"%s\" are isomorphic\n", str3, str4);
    } else {
        printf("\"%s\" and \"%s\" are not isomorphic\n", str3, str4);
    }

    return 0;
}