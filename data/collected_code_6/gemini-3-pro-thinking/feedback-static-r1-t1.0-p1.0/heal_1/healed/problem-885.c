#include <stdio.h>
#include <stdbool.h>

bool are_isomorphic(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return false;
    }

    int map1[256];
    int map2[256];

    for (int i = 0; i < 256; i++) {
        map1[i] = -1;
        map2[i] = -1;
    }

    while (*s1 != '\0' && *s2 != '\0') {
        unsigned char c1 = (unsigned char)*s1;
        unsigned char c2 = (unsigned char)*s2;

        if (map1[c1] == -1 && map2[c2] == -1) {
            map1[c1] = c2;
            map2[c2] = c1;
        } else if (map1[c1] != c2 || map2[c2] != c1) {
            return false;
        }
        s1++;
        s2++;
    }

    return *s1 == '\0' && *s2 == '\0';
}

int main(void) {
    const char *test1_str1 = "egg";
    const char *test1_str2 = "add";

    const char *test2_str1 = "foo";
    const char *test2_str2 = "bar";

    const char *test3_str1 = "paper";
    const char *test3_str2 = "title";

    bool result1 = are_isomorphic(test1_str1, test1_str2);
    bool result2 = are_isomorphic(test2_str1, test2_str2);
    bool result3 = are_isomorphic(test3_str1, test3_str2);

    printf("%s and %s: %d\n", test1_str1, test1_str2, result1);
    printf("%s and %s: %d\n", test2_str1, test2_str2, result2);
    printf("%s and %s: %d\n", test3_str1, test3_str2, result3);

    return 0;
}