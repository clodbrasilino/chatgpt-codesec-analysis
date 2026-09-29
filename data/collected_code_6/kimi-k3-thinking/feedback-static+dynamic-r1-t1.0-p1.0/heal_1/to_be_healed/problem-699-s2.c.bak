#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got <no output>
  *  test case 2 failed: expected 3, got <no output>
  *  test case 0 failed: expected 1, got <no output>
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

    len1 = strlen(s1);
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
    const char str1[] = "1101";
    const char str2[] = "0111";
    int result = min_swaps(str1, str2);

    if (result < 0) {
        printf("Conversion not possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    return 0;
}