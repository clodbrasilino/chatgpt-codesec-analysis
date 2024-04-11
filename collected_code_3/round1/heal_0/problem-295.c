#include <stdio.h>

int sum_of_divisors(int num) {
    int sum = 0;
    for(int i = 1; i <= num; i++) {
        if(num % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Sum of all divisors of %d is %d\n", num, sum_of_divisors(num));
    return 0;
}