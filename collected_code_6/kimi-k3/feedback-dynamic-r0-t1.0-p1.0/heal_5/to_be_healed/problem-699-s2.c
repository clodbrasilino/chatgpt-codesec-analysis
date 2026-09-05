#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int min_swaps(const char *str1, const char *str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    
    if (len1 != len2) {
        return -1;
    }

    int count0_str1 = 0, count1_str1 = 0;
    int count0_str2 = 0, count1_str2 = 0;

    for (size_t i = 0; i < len1; i++) {
        if (str1[i] == '0') count0_str1++;
        else if (str1[i] == '1') count1_str1++;
        else return -1;

        if (str2[i] == '0') count0_str2++;
        else if (str2[i] == '1') count1_str2++;
        else return -1;
    }

    if (count0_str1 != count0_str2 || count1_str1 != count1_str2) {
        return -1;
    }

    int swaps = 0;
    for (size_t i = 0; i < len1; i++) {
        if (str1[i] != str2[i]) {
            swaps++;
        }
    }

    return swaps / 2;
}

int main(void) {
    char str1[100], str2[100];
    
    if (scanf("%99s", str1) != 1) {
        printf("Not Possible\n");
        return 1;
    }
    
    if (scanf("%99s", str2) != 1) {
        printf("Not Possible\n");
        return 1;
    }

    int result = min_swaps(str1, str2);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}