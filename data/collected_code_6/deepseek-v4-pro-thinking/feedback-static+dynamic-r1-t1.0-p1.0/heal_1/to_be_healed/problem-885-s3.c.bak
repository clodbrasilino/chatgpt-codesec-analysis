#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isIsomorphic(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        return false;
    }

    size_t len_s = strlen(s);
    size_t len_t = strlen(t);

    if (len_s != len_t) {
        return false;
    }

    int map_s_t[256];
    int map_t_s[256];

    for (size_t i = 0; i < 256; i++) {
        map_s_t[i] = -1;
        map_t_s[i] = -1;
    }

    for (size_t i = 0; i < len_s; i++) {
        unsigned char c1 = (unsigned char)s[i];
        unsigned char c2 = (unsigned char)t[i];

        if (map_s_t[c1] == -1 && map_t_s[c2] == -1) {
            map_s_t[c1] = c2;
            map_t_s[c2] = c1;
        } else if (map_s_t[c1] != c2 || map_t_s[c2] != c1) {
            return false;
        }
    }

    return true;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 's1' can be declared as const array [constVariable]
     */
    char s1[] = "egg";
    /* Possible weaknesses found:
     *  Variable 't1' can be declared as const array [constVariable]
     */
    char t1[] = "add";
    /* Possible weaknesses found:
     *  Variable 's2' can be declared as const array [constVariable]
     */
    char s2[] = "foo";
    /* Possible weaknesses found:
     *  Variable 't2' can be declared as const array [constVariable]
     */
    char t2[] = "bar";
    /* Possible weaknesses found:
     *  Variable 's3' can be declared as const array [constVariable]
     */
    char s3[] = "paper";
    /* Possible weaknesses found:
     *  Variable 't3' can be declared as const array [constVariable]
     */
    char t3[] = "title";

    printf("%d\n", isIsomorphic(s1, t1));
    printf("%d\n", isIsomorphic(s2, t2));
    printf("%d\n", isIsomorphic(s3, t3));

    return 0;
}