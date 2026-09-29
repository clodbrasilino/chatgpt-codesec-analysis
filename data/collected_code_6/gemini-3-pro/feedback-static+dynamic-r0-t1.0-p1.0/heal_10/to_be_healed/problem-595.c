#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'Not Possible', got -1
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int min_swaps(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    int count_0_to_1 = 0;
    int count_1_to_0 = 0;
    int i = 0;

    while (str1[i] != '\0' && str2[i] != '\0') {
        if ((str1[i] != '0' && str1[i] != '1') || 
            (str2[i] != '0' && str2[i] != '1')) {
            return -1;
        }

        if (str1[i] == '0' && str2[i] == '1') {
            count_0_to_1++;
        } else if (str1[i] == '1' && str2[i] == '0') {
            count_1_to_0++;
        }
        i++;
    }

    if (str1[i] != '\0' || str2[i] != '\0') {
        return -1;
    }

    if (count_0_to_1 != count_1_to_0) {
        return -1;
    }

    return count_0_to_1;
}

int main(void) {
    char *str1 = malloc(100005 * sizeof(char));
    char *str2 = malloc(100005 * sizeof(char));

    if (str1 == NULL || str2 == NULL) {
        free(str1);
        free(str2);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%100004s %100004s", str1, str2) == 2) {
        int result = min_swaps(str1, str2);

        if (result != -1) {
            printf("%d\n", result);
        } else {
            printf("Not Possible\n");
        }
    } else {
        printf("Not Possible\n");
    }

    free(str1);
    free(str2);

    return 0;
}