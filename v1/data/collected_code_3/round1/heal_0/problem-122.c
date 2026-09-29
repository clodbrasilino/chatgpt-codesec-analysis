#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isSmartNumber(int num) {
    int val = (int)sqrt(num);
    return (val*val == num);
}

int nthSmartNumber(int n) {
    int count = 0;
    for (int num = 1; ; num++) {
        if (isSmartNumber(num))
            count++;
        if (count == n)
            return num;
    }
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("%d\n", nthSmartNumber(n));
    return 0;
}