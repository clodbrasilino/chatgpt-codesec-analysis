#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isIsomorphic(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        return false;
    }

    int map_s[256];
    int map_t[256];

    for (int i = 0; i < 256; i++) {
        map_s[i] = -1;
        map_t[i] = -1;
    }

    size_t i = 0;
    while (s[i] != '\0' && t[i] != '\0') {
        unsigned char c1 = (unsigned char)s[i];
        unsigned char c2 = (unsigned char)t[i];

        if (map_s[c1] == -1 && map_t[c2] == -1) {
            map_s[c1] = c2;
            map_t[c2] = c1;
        } else if (map_s[c1] != c2 || map_t[c2] != c1) {
            return false;
        }
        i++;
    }

    return s[i] == '\0' && t[i] == '\0';
}

int main(int argc, const char *const argv[]) {
    char s[65536];
    char t[65536];

    if (argc >= 3) {
        if (isIsomorphic(argv[1], argv[2])) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    } else {
        if (scanf("%65535s %65535s", s, t) == 2) {
            if (isIsomorphic(s, t)) {
                printf("True\n");
            } else {
                printf("False\n");
            }
        }
    }

    return 0;
}