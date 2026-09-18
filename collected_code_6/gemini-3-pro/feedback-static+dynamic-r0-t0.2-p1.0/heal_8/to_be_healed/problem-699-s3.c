#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    int count1[256] = {0};
    int count2[256] = {0};
    int mismatches = 0;

    for (size_t i = 0; i < len1; i++) {
        count1[(unsigned char)str1[i]]++;
        count2[(unsigned char)str2[i]]++;
        if (str1[i] != str2[i]) {
            mismatches++;
        }
    }

    for (int i = 0; i < 256; i++) {
        if (count1[i] != count2[i]) {
            return -1;
        }
    }

    return mismatches / 2;
}

int main(void) {
    char a[100005];
    char b[100005];

    if (scanf("%100004s %100004s", a, b) >= 1) {
        if (a[0] != '\0' && b[0] != '\0') {
            int result = min_swaps(a, b);
            if (result != -1) {
                printf("%d\n", result);
            } else {
                printf("Not Possible\n");
            }
        }
    }

    return 0;
}