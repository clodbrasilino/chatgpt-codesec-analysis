#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool are_isomorphic(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    int map1[256];
    int map2[256];
    size_t i;
    unsigned char c1;
    unsigned char c2;

    if (s1 == NULL || s2 == NULL) {
        return false;
    }

    len1 = strlen(s1);
    len2 = strlen(s2);

    if (len1 != len2) {
        return false;
    }

    for (i = 0; i < 256; i++) {
        map1[i] = -1;
        map2[i] = -1;
    }

    for (i = 0; i < len1; i++) {
        c1 = (unsigned char)s1[i];
        c2 = (unsigned char)s2[i];

        if (map1[c1] == -1 && map2[c2] == -1) {
            map1[c1] = (int)c2;
            map2[c2] = (int)c1;
        } else if (map1[c1] != (int)c2 || map2[c2] != (int)c1) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const char *test1a = "egg";
    const char *test1b = "add";
    const char *test2a = "foo";
    const char *test2b = "bar";
    const char *test3a = "paper";
    const char *test3b = "title";

    if (are_isomorphic(test1a, test1b)) {
        printf("\"%s\" and \"%s\" are isomorphic\n", test1a, test1b);
    } else {
        printf("\"%s\" and \"%s\" are not isomorphic\n", test1a, test1b);
    }

    if (are_isomorphic(test2a, test2b)) {
        printf("\"%s\" and \"%s\" are isomorphic\n", test2a, test2b);
    } else {
        printf("\"%s\" and \"%s\" are not isomorphic\n", test2a, test2b);
    }

    if (are_isomorphic(test3a, test3b)) {
        printf("\"%s\" and \"%s\" are isomorphic\n", test3a, test3b);
    } else {
        printf("\"%s\" and \"%s\" are not isomorphic\n", test3a, test3b);
    }

    return EXIT_SUCCESS;
}