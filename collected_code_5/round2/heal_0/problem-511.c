#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minSumOfFactors(int n) {

    int sum = 0; 
    if (n <= 3)
        return n;

    while (n % 2 == 0) {
        sum += 2;
        n /= 2;
    }
  
    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            sum += i;
            n /= i;
        }
    }

    if (n > 2)
        sum += n;

    return sum;
}

int main() {
    int num; 
    printf("Enter a number: ");
    if(scanf("%d", &num) != 1){
        printf("Invalid input. Please enter a number.\n");
        exit(0);
    }
    int result = minSumOfFactors(num);
    printf("Minimum sum of the factors of the number is: %d\n", result);
    return 0;
}