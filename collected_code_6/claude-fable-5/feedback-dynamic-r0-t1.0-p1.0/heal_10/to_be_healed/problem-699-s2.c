#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int min_swaps(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;
    int diff10 = 0;
    int diff01 = 0;

    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    len1 = strlen(s1);
    len2 = strlen(s2);

    if (len1 != len2) {
        return -1;
    }

    for (i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') || (s2[i] != '0' && s2[i] != '1')) {
            return -1;
        }
        if (s1[i] == '1' && s2[i] == '0') {
            diff10++;
        } else if (s1[i] == '0' && s2[i] == '1') {
            diff01++;
        }
    }

    if (diff10 != diff01) {
        return -1;
    }

    return diff10;
}

int print_result(int result)
{
    if (result < 0) {
        if (printf("Not Possible\n") < 0) {
            return -1;
        }
    } else {
        if (printf("Minimum swaps required: %d\n", result) < 0) {
            return -1;
        }
    }
    return 0;
}

int main(void)
{
    const char *str1 = "1101";
    const char *str2 = "0011";
    int result;

    result = min_swaps(str1, str2);

    if (print_result(result) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}