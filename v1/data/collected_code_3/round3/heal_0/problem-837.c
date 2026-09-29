#include <stdio.h>

int cubeSumOdd(int n) {
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        int oddNum = 2 * i - 1;
        sum += oddNum * oddNum * oddNum;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Cube sum of first %d odd natural numbers is %d\n", n, cubeSumOdd(n));
    return 0;
}