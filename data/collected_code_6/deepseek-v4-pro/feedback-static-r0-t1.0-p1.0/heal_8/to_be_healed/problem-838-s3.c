#include <stdio.h>
#include <string.h>

int minSwaps(const char *s1, const char *s2) {
    if (!s1 || !s2) return -1;

    size_t len = strnlen(s1, 101);
    if (len == 0 || len > 100) return -1;

    if (strnlen(s2, 101) != len) return -1;

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
    char s1[103] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s2[103] = {0};

    printf("Enter first binary string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%102s", s1) != 1) {
        printf("-1\n");
        return 0;
    }

    printf("Enter second binary string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%102s", s2) != 1) {
        printf("-1\n");
        return 0;
    }

    size_t len1 = strnlen(s1, sizeof(s1));
    size_t len2 = strnlen(s2, sizeof(s2));

    if (len1 != len2 || len1 == 0 || len1 > 100) {
        printf("-1\n");
        return 0;
    }

    for (size_t i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') || (s2[i] != '0' && s2[i] != '1')) {
            printf("-1\n");
            return 0;
        }
    }

    int result = minSwaps(s1, s2);
    printf("%d\n", result);

    return 0;
}