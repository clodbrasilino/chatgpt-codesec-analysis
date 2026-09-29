#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 1024
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int min_swaps(const char *s1, const char *s2)
{
    size_t i;
    size_t len1;
    size_t len2;
    int count10 = 0;
    int count01 = 0;

    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    len1 = strnlen(s1, MAX_STR_LEN + 1);
    len2 = strnlen(s2, MAX_STR_LEN + 1);

    if (len1 > MAX_STR_LEN || len2 > MAX_STR_LEN) {
        return -1;
    }

    if (len1 != len2) {
        return -1;
    }

    for (i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') ||
            (s2[i] != '0' && s2[i] != '1')) {
            return -1;
        }
        if (s1[i] == '1' && s2[i] == '0') {
            count10++;
        } else if (s1[i] == '0' && s2[i] == '1') {
            count01++;
        }
    }

    if (count10 != count01) {
        return -1;
    }

    return count10;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[MAX_STR_LEN + 1];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[MAX_STR_LEN + 1];

    while (scanf("%" TOSTRING(MAX_STR_LEN) "s %" TOSTRING(MAX_STR_LEN) "s",
                 str1, str2) == 2) {
        int result;

        str1[MAX_STR_LEN] = '\0';
        str2[MAX_STR_LEN] = '\0';

        result = min_swaps(str1, str2);

        if (result < 0) {
            printf("Not Possible\n");
        } else {
            printf("%d\n", result);
        }
    }

    return 0;
}