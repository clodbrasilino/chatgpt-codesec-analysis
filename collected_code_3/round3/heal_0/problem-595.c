#include <stdio.h>
#include <string.h>

int minSwaps(char *str1, char *str2, int n) {
    int count1 = 0, count2 = 0;
    int result = 0;

    for (int i = 0; i < n; i++) {
        if (str1[i] != str2[i]) {
            if (str1[i] == '1')
                count1++;
            else
                count2++;
        }
    }

    result = (count1 + count2) / 2;

    if (count1 % 2 != count2 % 2)
        return -1;
    else
        return result + (count1 % 2);
}

int main() {
    char str1[] = "1100";
    char str2[] = "0011";
    int n = strlen(str1);

    int result = minSwaps(str1, str2, n);

    if (result != -1)
        printf("Minimum number of swaps required is %d\n", result);
    else
        printf("Conversion is not possible\n");

    return 0;
}