#include<stdio.h>
#include<math.h>

long long int fifth_power_sum(int n) {
    long long int sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += pow(i, 5);
    }
    return sum;
}

int main() {
    int num;
    printf("\nEnter a number: ");
    scanf("%d", &num);
    
    if(num <= 0) {
        printf("\nInvalid input. Please input a positive number.");
        return 0;
    }
    
    long long int result = fifth_power_sum(num);
    printf("\nThe sum of fifth powers of first %d natural numbers is: %lld", num, result);
    
    return 0;
}