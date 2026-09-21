#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

bool is_isomorphic(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        return false;
    }

    size_t len_s = 0;
    size_t len_t = 0;

    while (len_s < SIZE_MAX && s[len_s] != '\0') {
        len_s++;
    }

    while (len_t < SIZE_MAX && t[len_t] != '\0') {
        len_t++;
    }

    if (len_s != len_t) {
        return false;
    }

    if (len_s > SIZE_MAX / 2) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char map_s_to_t[UCHAR_MAX + 1];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char map_t_to_s[UCHAR_MAX + 1];

    memset(map_s_to_t, 0, sizeof(map_s_to_t));
    memset(map_t_to_s, 0, sizeof(map_t_to_s));

    for (size_t i = 0; i < len_s; i++) {
        unsigned char c1 = (unsigned char)s[i];
        unsigned char c2 = (unsigned char)t[i];

        if (map_s_to_t[c1] == 0 && map_t_to_s[c2] == 0) {
            map_s_to_t[c1] = c2;
            map_t_to_s[c2] = c1;
        } else if (map_s_to_t[c1] != c2 || map_t_to_s[c2] != c1) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const char *s1 = "egg";
    const char *t1 = "add";
    const char *s2 = "foo";
    const char *t2 = "bar";
    const char *s3 = "paper";
    const char *t3 = "title";
    const char *s4 = "ab";
    const char *t4 = "aa";

    printf("%s and %s: %s\n", s1, t1, is_isomorphic(s1, t1) ? "true" : "false");
    printf("%s and %s: %s\n", s2, t2, is_isomorphic(s2, t2) ? "true" : "false");
    printf("%s and %s: %s\n", s3, t3, is_isomorphic(s3, t3) ? "true" : "false");
    printf("%s and %s: %s\n", s4, t4, is_isomorphic(s4, t4) ? "true" : "false");

    return 0;
}