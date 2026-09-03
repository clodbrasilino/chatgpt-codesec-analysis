#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_swaps(const char *str1, const char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int count01 = 0, count10 = 0;
    int i;

    if (len1 != len2) {
        return -1;
    }

    for (i = 0; i < len1; i++) {
        if (str1[i] == '0' && str2[i] == '1') {
            count01++;
        } else if (str1[i] == '1' && str2[i] == '0') {
            count10++;
        } else if (str1[i] != str2[i]) {
            return -1;
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
    if (scanf("%99s", str1) != 1) {
        return 1;
    }
    printf("Enter second binary string: ");
    if (scanf("%99s", str2) != 1) {
        return 1;
    }

    for (int i = 0; str1[i] != '\0'; i++) {
        if (str1[i] != '0' && str1[i] != '1') {
            printf("Not Possible\n");
            return 0;
        }
    }
    for (int i = 0; str2[i] != '\0'; i++) {
        if (str2[i] != '0' && str2[i] != '1') {
            printf("Not Possible\n");
            return 0;
        }
    }

    int result = min_swaps(str1, str2);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}