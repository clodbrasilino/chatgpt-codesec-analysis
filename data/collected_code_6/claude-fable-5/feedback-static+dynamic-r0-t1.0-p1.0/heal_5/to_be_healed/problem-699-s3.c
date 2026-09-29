#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LEN 4096

static void strip_newline(char *s)
{
    size_t len;

    if (s == NULL) {
        return;
    }

    len = strnlen(s, MAX_INPUT_LEN + 2);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        len--;
    }
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got 2
  *  test case 1 failed: expected 'Not Possible', got -1
  *  test case 2 failed: expected 3, got 4
  */

int min_swaps(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;
    int count01 = 0;
    int count10 = 0;
    int result;

    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    len1 = strnlen(s1, MAX_INPUT_LEN + 1);
    len2 = strnlen(s2, MAX_INPUT_LEN + 1);

    if (len1 > MAX_INPUT_LEN || len2 > MAX_INPUT_LEN) {
        return -1;
    }

    if (len1 != len2 || len1 == 0) {
        return -1;
    }

    for (i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') ||
            (s2[i] != '0' && s2[i] != '1')) {
            return -1;
        }
        if (s1[i] != s2[i]) {
            if (s1[i] == '0') {
                count01++;
            } else {
                count10++;
            }
        }
    }

    if ((count01 + count10) % 2 != 0) {
        return -1;
    }

    result = count01 / 2 + count10 / 2;
    if (count01 % 2 != 0) {
        result += 2;
    }

    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s1[MAX_INPUT_LEN + 2];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s2[MAX_INPUT_LEN + 2];
    int result;

    memset(s1, 0, sizeof(s1));
    memset(s2, 0, sizeof(s2));

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%4097s", s1) != 1) {
        if (printf("Not Possible\n") < 0) {
            return 1;
        }
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%4097s", s2) != 1) {
        if (printf("Not Possible\n") < 0) {
            return 1;
        }
        return 0;
    }

    strip_newline(s1);
    strip_newline(s2);

    result = min_swaps(s1, s2);

    if (result < 0) {
        if (printf("Not Possible\n") < 0) {
            return 1;
        }
    } else {
        if (printf("%d\n", result) < 0) {
            return 1;
        }
    }

    return 0;
}