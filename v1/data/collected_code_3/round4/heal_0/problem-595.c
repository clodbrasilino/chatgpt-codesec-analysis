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

    if (count1 != count2)
        return -1;

    count1 = 0;
    for (int i = 0; i < n; i++) {
        if (str1[i] != str2[i] && str1[i] == '1') {
            if (count1 > 0)
                count1--;
            else
                result++;
        }
        else if (str1[i] != str2[i] && str2[i] == '1') {
            count1++;
        }
    }

    return result;
}

int main() {
    char str1[] = "1100";
    char str2[] = "0011";
    int n = strlen(str1);
    printf("%d", minSwaps(str1, str2, n));
    return 0;
}