#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'Not Possible', got -1
  *  test case 1 failed: expected 'Not Possible', got -1
  */

long min_swaps(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;
    long count10 = 0;
    long count01 = 0;

    if (s1 == NULL || s2 == NULL) {
        return -1L;
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
        return -1L;
    }

    for (i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') ||
            (s2[i] != '0' && s2[i] != '1')) {
            return -1L;
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
        return -1L;
    }

    return count10;
}

int main(void)
{
    const char *a = "1101";
    const char *b = "0011";
    long result;

    result = min_swaps(a, b);

    if (result < 0) {
        if (fprintf(stderr, "Conversion not possible or invalid input\n") < 0) {
            return 1;
        }
        return 1;
    }

    if (printf("Minimum swaps required: %ld\n", result) < 0) {
        return 1;
    }

    return 0;
}