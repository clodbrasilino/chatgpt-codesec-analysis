#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool areIsomorphic(char* s1, char* s2) {
    if (strlen(s1) != strlen(s2)) {
        return false;
    }

    int len = strlen(s1);
    int map1[256] = {0}, map2[256] = {0};

    for (int i = 0; i < len; i++) {
        if (map1[(unsigned char)s1[i]] != map2[(unsigned char)s2[i]]) {
            return false;
        }
        map1[(unsigned char)s1[i]] = i + 1;
        map2[(unsigned char)s2[i]] = i + 1;
    }
    return true;
}

int main() {
    char *s1 = "paper";
    char *s2 = "title";

    if (areIsomorphic(s1, s2)) {
        printf("The strings are isomorphic.\n");
    } else {
        printf("The strings are not isomorphic.\n");
    }

    return 0;
}