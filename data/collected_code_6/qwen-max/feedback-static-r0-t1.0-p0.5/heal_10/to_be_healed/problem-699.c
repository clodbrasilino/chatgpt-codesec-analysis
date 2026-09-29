#include <stdio.h>
#include <string.h>

int minSwaps(const char *s1, const char *s2, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (s1[i] == '\0' || s2[i] == '\0') return -1;
    }
    int count[2] = {0, 0};
    for (size_t i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            count[s1[i] - '0']++;
        }
    }
    return (count[0] == count[1]) ? count[0] : -1;
}

int main() {
    const char s1[] = "1100";
    const char s2[] = "1001";

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  Assignment 'len1=strlen(s1)', assigned value is 4
     */
    size_t len1 = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(s2);

    /* Possible weaknesses found:
     *  Condition 'len1!=len2' is always false [knownConditionTrueFalse]
     *  Condition 'len1!=len2' is always false
     */
    if (len1 != len2) return -1;

    int result = minSwaps(s1, s2, len1);
    if (result != -1) {
        printf("Minimum swaps required: %d\n", result);
    } else {
        printf("Conversion not possible\n");
    }
    return 0;
}