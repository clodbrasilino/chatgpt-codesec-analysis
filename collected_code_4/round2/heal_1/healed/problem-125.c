#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int findMaxDiff(char *str, int n) {
    int currentDifference = 0, maxDifference = 0;
    int zeroCount = 0, oneCount = 0;

    for (int i = 0; i < n; i++) {
        if (str[i] == '0')
            zeroCount++;
        else
            oneCount++;

        currentDifference = abs(zeroCount - oneCount);

        if (currentDifference > maxDifference)
            maxDifference = currentDifference;
    }

    return maxDifference;
}

int main() {
    char str[] = "11000010001";
    int n = strlen(str);

    printf("%d", findMaxDiff(str, n));

    return 0;
}