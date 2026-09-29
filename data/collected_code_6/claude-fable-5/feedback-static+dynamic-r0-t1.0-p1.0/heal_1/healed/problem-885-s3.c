#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STR_LEN 4096U

bool are_isomorphic(const char *s1, const char *s2)
{
    int map1[256];
    int map2[256];
    size_t len1;
    size_t len2;
    size_t i;

    if (s1 == NULL || s2 == NULL) {
        return false;
    }

    len1 = strnlen(s1, MAX_STR_LEN);
    len2 = strnlen(s2, MAX_STR_LEN);

    if (len1 >= MAX_STR_LEN || len2 >= MAX_STR_LEN) {
        return false;
    }

    if (len1 != len2) {
        return false;
    }

    for (i = 0; i < 256; i++) {
        map1[i] = -1;
        map2[i] = -1;
    }

    for (i = 0; i < len1; i++) {
        const unsigned char c1 = (unsigned char)s1[i];
        const unsigned char c2 = (unsigned char)s2[i];

        if (map1[c1] == -1 && map2[c2] == -1) {
            map1[c1] = (int)c2;
            map2[c2] = (int)c1;
        } else if (map1[c1] != (int)c2 || map2[c2] != (int)c1) {
            return false;
        }
    }

    return true;
}

static void print_result(const char *a, const char *b)
{
    if (are_isomorphic(a, b)) {
        printf("\"%s\" and \"%s\" are isomorphic\n", a, b);
    } else {
        printf("\"%s\" and \"%s\" are not isomorphic\n", a, b);
    }
}

int main(void)
{
    const char *test1a = "egg";
    const char *test1b = "add";
    const char *test2a = "foo";
    const char *test2b = "bar";
    const char *test3a = "paper";
    const char *test3b = "title";

    print_result(test1a, test1b);
    print_result(test2a, test2b);
    print_result(test3a, test3b);

    return EXIT_SUCCESS;
}