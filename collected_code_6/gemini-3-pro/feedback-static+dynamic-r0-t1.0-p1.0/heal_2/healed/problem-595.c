#include <stdio.h>

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
    char str1[10000];
    char str2[10000];

    if (scanf("%9999s %9999s", str1, str2) == 2) {
        int result = min_swaps(str1, str2);

        if (result != -1) {
            printf("%d\n", result);
        } else {
            printf("Not Possible\n");
        }
    }

    return 0;
}