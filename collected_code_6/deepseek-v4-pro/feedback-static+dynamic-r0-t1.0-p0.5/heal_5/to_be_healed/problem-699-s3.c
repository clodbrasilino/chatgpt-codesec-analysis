#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int min_swaps(const char *str1, const char *str2) {
    int len = strlen(str1);
    int count01 = 0, count10 = 0;
    int i;

    if (strlen(str1) != strlen(str2)) {
        return -1;
    }

    for (i = 0; i < len; i++) {
        if (str1[i] != str2[i]) {
            if (str1[i] == '0' && str2[i] == '1') {
                count01++;
            } else if (str1[i] == '1' && str2[i] == '0') {
                count10++;
            } else {
                return -1;
            }
        }
    }

    if (count01 != count10) {
        return -1;
    }

    return count01;
}

int main(void) {
    char str1[100], str2[100];

    printf("Enter first binary string: ");
    scanf("%99s", str1);
    printf("Enter second binary string: ");
    scanf("%99s", str2);

    if (strlen(str1) != strlen(str2)) {
        printf("Strings must be of equal length\n");
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