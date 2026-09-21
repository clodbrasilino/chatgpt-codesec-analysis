#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

bool areIsomorphic(const char *s1, const char *s2) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(s1) != strlen(s2)) return false;

    int m1[256] = {0}, m2[256] = {0};
    for (int i = 0; s1[i] && s2[i]; i++) {
        char c1 = s1[i], c2 = s2[i];
        if (m1[c1] != m2[c2]) return false;
        m1[c1] = i + 1;
        m2[c2] = i + 1;
    }
    return true;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'str1' can be declared as pointer to const [constVariablePointer]
     */
    char *str1 = "egg";
    /* Possible weaknesses found:
     *  Variable 'str2' can be declared as pointer to const [constVariablePointer]
     */
    char *str2 = "add";

    if (areIsomorphic(str1, str2)) {
        printf("The strings are isomorphic.\n");
    } else {
        printf("The strings are not isomorphic.\n");
    }

    return 0;
}