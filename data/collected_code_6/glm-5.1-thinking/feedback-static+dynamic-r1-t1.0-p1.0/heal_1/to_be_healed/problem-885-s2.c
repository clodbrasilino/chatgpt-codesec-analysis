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

    int s_to_t[256];
    int t_to_s[256];

    memset(s_to_t, -1, sizeof(s_to_t));
    memset(t_to_s, -1, sizeof(t_to_s));

    for (size_t i = 0; i < len_s; i++) {
        unsigned char c1 = (unsigned char)s[i];
        unsigned char c2 = (unsigned char)t[i];

        if (s_to_t[c1] == -1 && t_to_s[c2] == -1) {
            s_to_t[c1] = c2;
            t_to_s[c2] = c1;
        } else if (s_to_t[c1] != c2 || t_to_s[c2] != c1) {
            return 0;
        }
    }

    return 1;
}

int main() {
    const char *str1 = "egg";
    const char *str2 = "add";
    const char *str3 = "foo";
    const char *str4 = "bar";
    const char *str5 = "paper";
    const char *str6 = "title";

    printf("%d\n", areIsomorphic(str1, str2));
    printf("%d\n", areIsomorphic(str3, str4));
    printf("%d\n", areIsomorphic(str5, str6));
    printf("%d\n", areIsomorphic(NULL, str1));

    return 0;
}