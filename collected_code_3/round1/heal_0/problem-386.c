#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minSwaps(char exp[], int n) {
    int count = 0;
    int swap = 0;
    int temp = 0;
    int i;

    for (i = 0; i < n; i++) {
        if (exp[i] == '[') {
            count++;
            temp++;
        } else if (exp[i] == ']') {
            count--;
        }
        if (count < 0) {
            swap += abs(count);
            count = 1;
        }
    }
    return swap;
}

int main() {
    char exp[] = "[]][][";
    int n = strlen(exp);
    printf("%d\n", minSwaps(exp, n));
    return 0;
}