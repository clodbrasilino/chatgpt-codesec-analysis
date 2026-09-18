#include <stdio.h>

int findMaxSum(int n) {
    if(n < 2) return 0;
    if(n == 2) return 1;

    /* Possible weaknesses found:
     *  implicit declaration of function 'max' [-Wimplicit-function-declaration]
     */
    return max(n, findMaxSum(n/2) + findMaxSum(n/3) + findMaxSum(n/4));
}

int max(int a, int b) {
    return (a>b)? a : b;
}

int main() {
    int num = 24;
    printf("Maximum sum is %d \n", findMaxSum(num));

    return 0;
}