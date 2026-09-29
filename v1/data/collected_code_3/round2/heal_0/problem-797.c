#include <stdio.h>

int sumOddNumbers(int l, int r) {
    int sum = 0;
    for(int i = l; i <= r; i++) {
        if(i % 2 != 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int l, r;
    printf("Enter the range (l, r): ");
    scanf("%d %d", &l, &r);
    int sum = sumOddNumbers(l, r);
    printf("Sum of all odd numbers between %d and %d is: %d\n", l, r, sum);
    return 0;
}