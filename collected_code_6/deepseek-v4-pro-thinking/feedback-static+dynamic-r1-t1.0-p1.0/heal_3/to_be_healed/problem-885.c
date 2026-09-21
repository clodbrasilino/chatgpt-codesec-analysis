#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAP_SIZE (UCHAR_MAX + 2)

bool isIsomorphic(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char map_s_t[MAP_SIZE] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char map_t_s[MAP_SIZE] = {0};

    for (size_t i = 0; ; i++) {
        unsigned char c1 = (unsigned char)s[i];
        unsigned char c2 = (unsigned char)t[i];

        if (c1 == '\0' && c2 == '\0') {
            break;
        }
        if (c1 == '\0' || c2 == '\0') {
            return false;
        }

        if (c1 >= MAP_SIZE || c2 >= MAP_SIZE) {
            return false;
        }

        if (map_s_t[c1] == 0 && map_t_s[c2] == 0) {
            map_s_t[c1] = c2;
            map_t_s[c2] = c1;
        } else if (map_s_t[c1] != c2 || map_t_s[c2] != c1) {
            return false;
        }
    }

    return true;
}

int main(void) {
    printf("%d\n", isIsomorphic("egg", "add"));
    printf("%d\n", isIsomorphic("foo", "bar"));
    printf("%d\n", isIsomorphic("paper", "title"));
    printf("%d\n", isIsomorphic("ab", "aa"));
    printf("%d\n", isIsomorphic("", ""));
    printf("%d\n", isIsomorphic(NULL, "a"));
    return 0;
}