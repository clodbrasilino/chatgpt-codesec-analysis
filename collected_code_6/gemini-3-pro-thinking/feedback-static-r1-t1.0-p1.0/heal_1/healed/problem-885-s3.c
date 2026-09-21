#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

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
    const char *str1 = "egg";
    const char *str2 = "add";
    
    if (are_isomorphic(str1, str2)) {
        printf("Isomorphic\n");
    } else {
        printf("Not isomorphic\n");
    }

    const char *str3 = "foo";
    const char *str4 = "bar";
    
    if (are_isomorphic(str3, str4)) {
        printf("Isomorphic\n");
    } else {
        printf("Not isomorphic\n");
    }

    return 0;
}