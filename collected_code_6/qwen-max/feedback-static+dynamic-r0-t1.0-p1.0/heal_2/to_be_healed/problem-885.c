#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool areIsomorphic(const char *s1, const char *s2) {
    int map_s1[128] = {0};
    int map_s2[128] = {0};

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(s1) != strlen(s2)) return false;

    for (int i = 0; s1[i] && s2[i]; i++) {
        if (map_s1[(unsigned char)s1[i]] != map_s2[(unsigned char)s2[i]]) return false;
        map_s1[(unsigned char)s1[i]] = i + 1;
        map_s2[(unsigned char)s2[i]] = i + 1;
    }

    return true;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'str1' can be declared as const array [constVariable]
     */
    char str1[] = "egg";
    /* Possible weaknesses found:
     *  Variable 'str2' can be declared as const array [constVariable]
     */
    char str2[] = "add";
    if (areIsomorphic(str1, str2))
        printf("Yes\n");
    else
        printf("No\n");

    /* Possible weaknesses found:
     *  Variable 'str3' can be declared as const array [constVariable]
     */
    char str3[] = "foo";
    /* Possible weaknesses found:
     *  Variable 'str4' can be declared as const array [constVariable]
     */
    char str4[] = "bar";
    if (areIsomorphic(str3, str4))
        printf("Yes\n");
    else
        printf("No\n");

    return 0;
}