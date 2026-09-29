#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool are_isomorphic(const char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL)
    {
        return false;
    }

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    if (len1 != len2)
    {
        return false;
    }

    int map1[256];
    int map2[256];

    for (int i = 0; i < 256; i++)
    {
        map1[i] = -1;
        map2[i] = -1;
    }

    for (size_t i = 0; i < len1; i++)
    {
        unsigned char c1 = (unsigned char)str1[i];
        unsigned char c2 = (unsigned char)str2[i];

        if (map1[c1] == -1 && map2[c2] == -1)
        {
            map1[c1] = (int)c2;
            map2[c2] = (int)c1;
        }
        else if (map1[c1] != (int)c2 || map2[c2] != (int)c1)
        {
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

    printf("\"%s\" and \"%s\" are %s\n", str1, str2,
           are_isomorphic(str1, str2) ? "isomorphic" : "not isomorphic");
    printf("\"%s\" and \"%s\" are %s\n", str3, str4,
           are_isomorphic(str3, str4) ? "isomorphic" : "not isomorphic");

    return 0;
}