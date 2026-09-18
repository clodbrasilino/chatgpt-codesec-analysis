#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str1[1000005];
char str2[1000005];

int main(void) {
    if (scanf("%1000004s", str1) != 1) return 0;
    if (scanf("%1000004s", str2) != 1) return 0;

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    if (len1 != len2) {
        printf("Not Possible\n");
        return 0;
    }

    int count_01 = 0;
    int count_10 = 0;

    for (size_t i = 0; i < len1; i++) {
        if (str1[i] == '0' && str2[i] == '1') {
            count_01++;
        } else if (str1[i] == '1' && str2[i] == '0') {
            count_10++;
        }
    }

    if (count_01 != count_10) {
        printf("Not Possible\n");
    } else {
        printf("%d\n", count_01);
    }

    return 0;
}