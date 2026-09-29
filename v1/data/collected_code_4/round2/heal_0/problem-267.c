#include <stdio.h>

int sumOfSquares(int n) {
    int sum = 0, oddNo = 1;
    for(int i = 0; i < n; i++) {
        sum += oddNo * oddNo;
        oddNo += 2;
    }
    return sum;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("The sum of squares of first %d odd natural numbers is %d\n", num, sumOfSquares(num));
    return 0;
}