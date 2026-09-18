#include <stdio.h>

long long int sumOfCubes(int n) {
    long long int sum = 0;
    int i;

    for (i = 2; i <= n * 2; i = i + 2) {
        sum += i * i * i;
    }

    return sum;
}

int main() {
    int n;
    
    printf("Enter a number:\n");
    scanf("%d", &n);
    
    if(n < 0){
        printf("Invalid input! Please enter a positive integer.\n");
        return -1;
    }
    
    printf("Cube sum of first %d even natural numbers is: %lld\n", n, sumOfCubes(n));
    return 0;
}