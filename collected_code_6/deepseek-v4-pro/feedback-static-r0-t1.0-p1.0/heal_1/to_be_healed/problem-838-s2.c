#include <stdio.h>
#include <string.h>

/* Possible weaknesses found:
 *  Parameter 's2' can be declared as pointer to const [constParameterPointer]
 */
int minSwapsToEqual(char *s1, char *s2) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(s1);
    int count1_s1 = 0, count1_s2 = 0;
    int type1 = 0, type2 = 0;

    for (int i = 0; i < len; i++) {
        if (s1[i] == '1') count1_s1++;
        if (s2[i] == '1') count1_s2++;
        if (s1[i] != s2[i]) {
            if (s1[i] == '0') type1++;
            else type2++;
        }
    }

    if (count1_s1 != count1_s2) return -1;
    if (type1 % 2 != 0 || type2 % 2 != 0) return -1;

    return type1 / 2 + type2 / 2 + (type1 % 2) * 2;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s1[100], s2[100];

    printf("Enter first binary string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%99s", s1) != 1) return 1;

    printf("Enter second binary string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%99s", s2) != 1) return 1;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(s1) != strlen(s2)) {
        printf("Strings must be of equal length\n");
        return 1;
    }

    int result = minSwapsToEqual(s1, s2);
    printf("Minimum swaps required: %d\n", result);

    return 0;
}