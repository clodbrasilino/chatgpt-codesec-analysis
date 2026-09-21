#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 2 failed: expected False, got <no output>
  */

bool isIsomorphic(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        return false;
    }

    int map_s[256] = {0};
    int map_t[256] = {0};

    size_t i = 0;
    while (s[i] != '\0' && t[i] != '\0') {
        unsigned char char_s = (unsigned char)s[i];
        unsigned char char_t = (unsigned char)t[i];

        if (map_s[char_s] == 0 && map_t[char_t] == 0) {
            map_s[char_s] = char_t;
            map_t[char_t] = char_s;
        } else if (map_s[char_s] != char_t || map_t[char_t] != char_s) {
            return false;
        }
        i++;
    }

    if (s[i] != '\0' || t[i] != '\0') {
        return false;
    }

    return true;
}

int main(void) {
    const char *str1 = "egg";
    const char *str2 = "add";
    
    if (isIsomorphic(str1, str2)) {
        printf("The strings \"%s\" and \"%s\" are isomorphic.\n", str1, str2);
    } else {
        printf("The strings \"%s\" and \"%s\" are not isomorphic.\n", str1, str2);
    }

    const char *str3 = "foo";
    const char *str4 = "bar";
    
    if (isIsomorphic(str3, str4)) {
        printf("The strings \"%s\" and \"%s\" are isomorphic.\n", str3, str4);
    } else {
        printf("The strings \"%s\" and \"%s\" are not isomorphic.\n", str3, str4);
    }

    return EXIT_SUCCESS;
}