#include <stdio.h>
#include <string.h>

int minSwaps(const char *s1, const char *s2) {
    int count[2] = {0, 0};
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(s2);
    if (s1[len1-1] != '\0' || s2[len2-1] != '\0') {
        return -1;
    }
    size_t len = (len1 < len2) ? len1 : len2;

    for (size_t i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '0' || s1[i] == '1') {
                count[s1[i] - '0']++;
            }
            if (s2[i] == '0' || s2[i] == '1') {
                count[s2[i] - '0']--;
            }
        }
    }

    return (count[0] + count[1]) / 2;
}

int main() {
    const char s1[] = "1100";
    const char s2[] = "1001";
    int result = minSwaps(s1, s2);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'count'
         *  'count' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         */
        printf("Minimum swaps required: %d\n", (count[0] + count[1]) / 2);
    }
    return 0;
}