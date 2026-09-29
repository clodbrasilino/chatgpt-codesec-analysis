#include <stdio.h>
#include <string.h>

int minSwaps(char *str1, char *str2, int n) {
    int count1 = 0, count2 = 0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (str1[i] != str2[i] && str1[i] == '1')
            count1++;
        else if (str1[i] != str2[i] && str1[i] == '0')
            count2++;
    }
    count = (count1 + count2) / 2;
    if (count1 % 2 == count2 % 2)
        return count + count1 % 2;
    return -1;
}

int main() {
    char str1[] = "1100";
    char str2[] = "0011";
    int n = strlen(str1);
    int result = minSwaps(str1, str2, n);
    if (result != -1)
        printf("Minimum swaps required is %d", result);
    else
        printf("Swapping is not possible");
    return 0;
}