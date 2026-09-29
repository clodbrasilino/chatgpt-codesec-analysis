#include <stdio.h>

long long int squareSum(int num) {
    long long int sum = 0;
    for(int i = 1; i <= num; i++) {
        sum += i * i;
    }
    return sum;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if(num < 1) {
        printf("Number must be greater than 0.\n");
        return -1;
    }

    long long int sum = squareSum(num);
    printf("Sum of square series till %d is %lld\n", num, sum);

    return 0;
}