#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int min_swaps(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    if (len1 != len2) {
        return -1;
    }

    int count_zero_to_one = 0;
    int count_one_to_zero = 0;

    for (size_t i = 0; i < len1; i++) {
        if (str1[i] != '0' && str1[i] != '1') {
            return -1;
        }
        if (str2[i] != '0' && str2[i] != '1') {
            return -1;
        }

        if (str1[i] == '0' && str2[i] == '1') {
            count_zero_to_one++;
        } else if (str1[i] == '1' && str2[i] == '0') {
            count_one_to_zero++;
        }
    }

    if (count_zero_to_one != count_one_to_zero) {
        return -1;
    }

    return count_zero_to_one;
}

int main(void) {
    const char *str1 = "1100";
    const char *str2 = "1001";

    int result = min_swaps(str1, str2);

    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Not Possible\n");
    }

    return 0;
}