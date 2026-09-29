#include <stdio.h>
#include <string.h>

int main(void) {
    char str1[100005];
    char str2[100005];

    if (scanf("%100004s %100004s", str1, str2) == 2) {
        size_t len1 = strlen(str1);
        size_t len2 = strlen(str2);

        if (len1 != len2) {
            printf("Not Possible\n");
            return 0;
        }

        int count_0_to_1 = 0;
        int count_1_to_0 = 0;

        for (size_t i = 0; i < len1; ++i) {
            if ((str1[i] != '0' && str1[i] != '1') || 
                (str2[i] != '0' && str2[i] != '1')) {
                printf("Not Possible\n");
                return 0;
            }

            if (str1[i] == '0' && str2[i] == '1') {
                count_0_to_1++;
            } else if (str1[i] == '1' && str2[i] == '0') {
                count_1_to_0++;
            }
        }

        if (count_0_to_1 != count_1_to_0) {
            printf("Not Possible\n");
        } else {
            printf("%d\n", count_0_to_1);
        }
    } else {
        printf("Not Possible\n");
    }

    return 0;
}