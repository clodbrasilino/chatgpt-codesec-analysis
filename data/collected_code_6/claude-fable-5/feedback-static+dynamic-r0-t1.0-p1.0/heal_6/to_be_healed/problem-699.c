#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LEN 4096

static size_t bounded_len(const char *s, size_t max_len)
{
    size_t i;

    for (i = 0; i < max_len; i++) {
        if (s[i] == '\0') {
            break;
        }
    }
    return i;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 'Not Possible', got <no output>
  */

int min_swaps(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;
    int count10 = 0;
    int count01 = 0;

    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    len1 = bounded_len(s1, MAX_INPUT_LEN);
    len2 = bounded_len(s2, MAX_INPUT_LEN);

    if (len1 >= MAX_INPUT_LEN || len2 >= MAX_INPUT_LEN) {
        return -1;
    }

    if (len1 != len2 || len1 == 0) {
        return -1;
    }

    for (i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') || (s2[i] != '0' && s2[i] != '1')) {
            return -1;
        }
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') {
                count10++;
            } else {
                count01++;
            }
        }
    }

    if (count10 != count01) {
        return -1;
    }

    return count10;
}

static void strip_newline(char *s)
{
    size_t len;

    if (s == NULL) {
        return;
    }

    len = bounded_len(s, MAX_INPUT_LEN);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        len--;
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s1[MAX_INPUT_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s2[MAX_INPUT_LEN];
    int result;

    memset(s1, 0, sizeof(s1));
    memset(s2, 0, sizeof(s2));

    if (fgets(s1, (int)sizeof(s1), stdin) == NULL) {
        return 1;
    }
    if (fgets(s2, (int)sizeof(s2), stdin) == NULL) {
        return 1;
    }

    s1[sizeof(s1) - 1] = '\0';
    s2[sizeof(s2) - 1] = '\0';

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

    if (fflush(stdout) != 0) {
        return 1;
    }

    return 0;
}