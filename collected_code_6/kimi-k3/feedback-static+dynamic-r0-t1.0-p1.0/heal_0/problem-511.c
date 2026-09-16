#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int minSumFactors(int n) {
    if (n <= 0) {
        return -1;
    }
    if (n == 1) {
        return 1;
    }
    
    int sum = 0;
    int temp = n;
    int i;
    
    while (temp % 2 == 0) {
        sum += 2;
        temp /= 2;
    }
    
    for (i = 3; i <= (int)sqrt((double)temp); i += 2) {
        while (temp % i == 0) {
            sum += i;
            temp /= i;
        }
    }
    
    if (temp > 2) {
        sum += temp;
    }
    
    return sum;
}

int main(void) {
    int num;
    int result;
    
    printf("Enter a positive integer: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    result = minSumFactors(num);
    if (result == -1) {
        fprintf(stderr, "Number must be positive\n");
        return EXIT_FAILURE;
    }
    
    printf("Minimum sum of factors of %d is: %d\n", num, result);
    
    return EXIT_SUCCESS;
}