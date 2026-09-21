#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH 4096

static size_t safeStrnlen(const char *s, size_t maxLen)
{
    size_t len = 0;
    while (len < maxLen && s[len] != '\0') {
        len++;
    }
    return len;
}

bool areIsomorphic(const char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    size_t len1 = safeStrnlen(str1, MAX_STRING_LENGTH);
    size_t len2 = safeStrnlen(str2, MAX_STRING_LENGTH);

    if (len1 != len2) {
        return false;
    }

    int map1[256];
    int map2[256];

    for (size_t i = 0; i < 256; i++) {
        map1[i] = -1;
        map2[i] = -1;
    }

    for (size_t i = 0; i < len1; i++) {
        unsigned char c1 = (unsigned char)str1[i];
        unsigned char c2 = (unsigned char)str2[i];

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
    const char *tests[][2] = {
        {"egg", "add"},
        {"foo", "bar"},
        {"paper", "title"},
        {"ab", "aa"},
        {"abc", "xyz"},
        {"", ""}
    };
    size_t numTests = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < numTests; i++) {
        bool result = areIsomorphic(tests[i][0], tests[i][1]);
        printf("\"%s\" and \"%s\" are %sisomorphic.\n",
               tests[i][0], tests[i][1], result ? "" : "not ");
    }

    return EXIT_SUCCESS;
}