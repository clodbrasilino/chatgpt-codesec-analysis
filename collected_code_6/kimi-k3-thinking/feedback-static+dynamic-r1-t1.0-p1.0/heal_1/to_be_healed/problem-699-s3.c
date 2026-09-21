#include <stdio.h>
#include <string.h>
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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len1 = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len2 = strlen(s2);

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
    const char *tests[][2] = {
        {"1100", "0011"},
        {"010", "100"},
        {"111", "000"},
        {"1010", "1010"},
        {"1001", "0110"}
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t t;

    for (t = 0; t < num_tests; t++) {
        int result = min_swaps(tests[t][0], tests[t][1]);
        if (result < 0) {
            printf("s1=%s s2=%s : conversion not possible\n",
                   tests[t][0], tests[t][1]);
        } else {
            printf("s1=%s s2=%s : minimum swaps = %d\n",
                   tests[t][0], tests[t][1], result);
        }
    }

    return 0;
}