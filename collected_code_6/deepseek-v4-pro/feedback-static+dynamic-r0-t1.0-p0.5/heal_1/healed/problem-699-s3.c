#include <stdio.h>
#include <string.h>

int min_swaps(const char *str1, const char *str2) {
    int len = strlen(str1);
    int count1 = 0, count2 = 0;
    int swaps = 0;
    int i;

    for (i = 0; i < len; i++) {
        if (str1[i] != str2[i]) {
            if (str1[i] == '0') {
                count1++;
            } else {
                count2++;
            }
        }
    }

    if (count1 != count2) {
        return -1;
    }

    swaps = count1 / 2;
    if (count1 % 2 != 0) {
        swaps++;
    }

    return swaps;
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