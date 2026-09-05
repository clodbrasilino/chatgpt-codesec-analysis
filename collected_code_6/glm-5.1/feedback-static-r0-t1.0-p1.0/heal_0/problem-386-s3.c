#include <stdio.h>
#include <stdlib.h>

int min_swaps(char *s) {
    int balance = 0;
    int swaps = 0;
    int total = 0;
    int i = 0;

    while (s[i] != '\0') {
        if (s[i] == '[') {
            balance++;
        } else {
            balance--;
        }
        if (balance < 0) {
            int j = i + 1;
            while (s[j] != '\0' && s[j] != '[') {
                j++;
            }
            if (s[j] == '\0') {
                return -1;
            }
            char temp = s[i];
            s[i] = s[j];
            s[j] = temp;
            swaps += j - i;
            balance = 1;
            total += swaps;
            swaps = 0;
        }
        i++;
    }
    if (balance != 0) {
        return -1;
    }
    return total;
}

int main() {
    char str1[] = "[]][][";
    int res1 = min_swaps(str1);
    printf("%d\n", res1);

    char str2[] = "[[][]]";
    int res2 = min_swaps(str2);
    printf("%d\n", res2);

    char str3[] = "[]][";
    int res3 = min_swaps(str3);
    printf("%d\n", res3);

    return 0;
}