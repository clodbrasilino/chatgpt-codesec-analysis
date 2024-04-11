#include <stdio.h>

int sum_of_positive_integers(int n) {
    int sum = 0;
    while(n > 0) {
        sum += n;
        n -= 2;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Sum of positive integers: %d\n", sum_of_positive_integers(n));
    return 0;
}