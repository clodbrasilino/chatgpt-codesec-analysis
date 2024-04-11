#include <stdio.h>

int sumEvenNumbers(int l, int r) {
    int sum = 0;
    for(int i = l; i <= r; i++) {
        if(i % 2 == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int l, r;
    printf("Enter the lower limit: ");
    scanf("%d", &l);
    printf("Enter the upper limit: ");
    scanf("%d", &r);
    int sum = sumEvenNumbers(l, r);
    printf("The sum of even numbers between %d and %d is: %d\n", l, r, sum);
    return 0;
}