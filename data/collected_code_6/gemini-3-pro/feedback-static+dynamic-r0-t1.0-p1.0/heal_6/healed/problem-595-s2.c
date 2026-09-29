#include <stdio.h>
#include <string.h>

int minSwaps(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    if (len1 != len2) {
        return -1;
    }

    int count_01 = 0;
    int count_10 = 0;

    for (size_t i = 0; i < len1; i++) {
        if ((str1[i] != '0' && str1[i] != '1') || (str2[i] != '0' && str2[i] != '1')) {
            return -1;
        }

        if (str1[i] == '0' && str2[i] == '1') {
            count_01++;
        } else if (str1[i] == '1' && str2[i] == '0') {
            count_10++;
        }
    }

    if (count_01 != count_10) {
        return -1;
    }

    return count_01;
}

int main(void) {
    char str1[200005];
    char str2[200005];

    if (scanf("%200004s", str1) == 1 && scanf("%200004s", str2) == 1) {
        int result = minSwaps(str1, str2);

        if (result != -1) {
            printf("%d\n", result);
        } else {
            printf("Not Possible\n");
        }
    } else {
        printf("Not Possible\n");
    }

    return 0;
}