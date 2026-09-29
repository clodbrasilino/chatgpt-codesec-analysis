#include <stdio.h>
#include <string.h>

int areIsomorphic(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len_s = strlen(s);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len_t = strlen(t);
    if (len_s != len_t) {
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char map_st[256] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char map_ts[256] = {0};
    for (size_t i = 0; i < len_s; i++) {
        unsigned char c_s = (unsigned char)s[i];
        unsigned char c_t = (unsigned char)t[i];
        if (map_st[c_s] == 0 && map_ts[c_t] == 0) {
            map_st[c_s] = c_t;
            map_ts[c_t] = c_s;
        } else {
            if (map_st[c_s] != c_t || map_ts[c_t] != c_s) {
                return 0;
            }
        }
    }
    return 1;
}

int main(void) {
    const char *str1 = "egg";
    const char *str2 = "add";
    const char *str3 = "foo";
    const char *str4 = "bar";
    const char *str5 = "paper";
    const char *str6 = "title";
    const char *str7 = NULL;
    const char *str8 = "abc";

    printf("%d\n", areIsomorphic(str1, str2));
    printf("%d\n", areIsomorphic(str3, str4));
    printf("%d\n", areIsomorphic(str5, str6));
    printf("%d\n", areIsomorphic(str7, str8));

    return 0;
}