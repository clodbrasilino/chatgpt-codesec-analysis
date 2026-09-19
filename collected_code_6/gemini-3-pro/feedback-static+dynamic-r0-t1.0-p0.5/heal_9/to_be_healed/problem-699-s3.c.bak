#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min_swaps(const char *str1, const char *str2, int n) {
    int count_01 = 0;
    int count_10 = 0;

    for (int i = 0; i < n; i++) {
        if (str1[i] == '0' && str2[i] == '1') {
            count_01++;
        } else if (str1[i] == '1' && str2[i] == '0') {
            count_10++;
        } else if (str1[i] != str2[i]) {
            return -1;
        }
    }

    if (count_01 != count_10) {
        return -1;
    }

    return count_01;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 0;
    }

    char *str1 = (char *)malloc((n + 5) * sizeof(char));
    char *str2 = (char *)malloc((n + 5) * sizeof(char));

    if (str1 == NULL || str2 == NULL) {
        if (str1) free(str1);
        if (str2) free(str2);
        return 0;
    }

    /* Possible weaknesses found:
     *  scanf() without field width limits can crash with huge input data. [invalidscanf]
     */
    if (scanf("%s", str1) == 1 && scanf("%s", str2) == 1) {
        int result = min_swaps(str1, str2, n);

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