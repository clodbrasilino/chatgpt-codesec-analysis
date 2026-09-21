#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

bool isIsomorphic(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        return false;
    }

    unsigned char *map_s = calloc(UCHAR_MAX + 1, sizeof(unsigned char));
    unsigned char *map_t = calloc(UCHAR_MAX + 1, sizeof(unsigned char));

    if (map_s == NULL || map_t == NULL) {
        free(map_s);
        free(map_t);
        return false;
    }

    while (*s != '\0' && *t != '\0') {
        unsigned char c1 = (unsigned char)*s;
        unsigned char c2 = (unsigned char)*t;

        if (map_s[c1] == 0 && map_t[c2] == 0) {
            map_s[c1] = c2;
            map_t[c2] = c1;
        } else if (map_s[c1] != c2 || map_t[c2] != c1) {
            free(map_s);
            free(map_t);
            return false;
        }

        s++;
        t++;
    }

    bool result = (*s == '\0' && *t == '\0');
    free(map_s);
    free(map_t);
    return result;
}

int main(void) {
    const char *slist[] = {"egg", "foo", "paper", "ab", "aa", "", "aba", NULL, "a"};
    const char *tlist[] = {"add", "bar", "title", "aa", "ab", "", "baa", "a", NULL};
    const bool expected[] = {true, false, true, false, false, true, false, false, false};

    int n = sizeof(slist) / sizeof(slist[0]);

    for (int i = 0; i < n; i++) {
        bool result = isIsomorphic(slist[i], tlist[i]);
        if (result == expected[i]) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }

    return 0;
}