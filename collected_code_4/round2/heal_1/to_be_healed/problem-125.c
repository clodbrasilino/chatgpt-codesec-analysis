#include<stdio.h>
#include<string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'abs'
  */

int findMaxDiff(char *str, int n) {
    int currentDifference = 0, maxDifference = 0;
    int zeroCount = 0, oneCount = 0;

    for (int i = 0; i < n; i++) {
        if (str[i] == '0')
            zeroCount = zeroCount + 1;
        else
            oneCount = oneCount + 1;

        /* Possible weaknesses found:
         *  implicit declaration of function 'abs' [-Wimplicit-function-declaration]
         */
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