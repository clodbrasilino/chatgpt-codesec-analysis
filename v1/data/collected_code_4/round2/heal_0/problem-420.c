#include<stdio.h>

long long int cubeSumOfEvenNumbers(int n) {
    long long int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i*i*i*4;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the number of even natural numbers: ");
    scanf("%d", &n);

    if(n<0){
        printf("Invalid input. Enter a non-negative number.\n");
        return -1;
    }

    long long int result = cubeSumOfEvenNumbers(n);
    
    printf("The sum of the cubes of the first %d even natural numbers is: %lld\n", n, result);

    return 0;
}