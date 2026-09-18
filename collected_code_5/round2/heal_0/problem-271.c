#include<stdio.h>
#include<math.h>

long long int fifthPowerSum(int n) {
    long long int sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += pow(i*2, 5);
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    if(n<0) {
        printf("Please enter positive integer\n");
        return 0;
    }
    printf("Sum of 5th power of first %d even natural numbers: %lld\n", n, fifthPowerSum(n));
    return 0;
}