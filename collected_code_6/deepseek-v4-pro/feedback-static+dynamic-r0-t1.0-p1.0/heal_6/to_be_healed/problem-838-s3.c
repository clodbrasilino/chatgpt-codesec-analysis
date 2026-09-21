#include <stdio.h>
#include <string.h>

int minSwaps(const char *s1, const char *s2, size_t len) {
    int count1 = 0, count2 = 0;

    for (size_t i = 0; i < len; i++) {
        if (s1[i] == '1') count1++;
        if (s2[i] == '1') count2++;
    }

    if (count1 != count2) {
        return -1;
    }

    int pos1 = 0, pos2 = 0;
    for (size_t i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') pos1++;
            else pos2++;
        }
    }

    if (pos1 % 2 == 0 && pos2 % 2 == 0) {
        return pos1 / 2 + pos2 / 2;
    } else if (pos1 % 2 == 1 && pos2 % 2 == 1) {
        return pos1 / 2 + pos2 / 2 + 2;
    }

    return -1;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s1[102] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s2[102] = {0};

    printf("Enter first binary string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%101s", s1) != 1) {
        printf("-1\n");
        return 0;
    }
    printf("Enter second binary string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%101s", s2) != 1) {
        printf("-1\n");
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(s2);

    if (len1 != len2 || len1 > 100) {
        printf("-1\n");
        return 0;
    }

    if (len1 == 0) {
        printf("0\n");
        return 0;
    }

    int result = minSwaps(s1, s2, len1);
    printf("%d\n", result);

    return 0;
}