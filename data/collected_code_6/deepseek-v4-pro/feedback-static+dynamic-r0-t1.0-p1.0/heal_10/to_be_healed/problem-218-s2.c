#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got 2
  *  test case 2 failed: expected 3, got 2
  */

int minOperations(int a, int b) {
    if (a == b) {
        return 0;
    }
    
    long long diff;
    if (a > b) {
        diff = (long long)a - b;
    } else {
        diff = (long long)b - a;
    }
    
    int operations = 0;
    
    operations += diff / 5;
    diff %= 5;
    
    operations += diff / 2;
    diff %= 2;
    
    operations += (int)diff;
    
    return operations;
}

int main(void) {
    int num1 = 0;
    int num2 = 0;
    
    printf("Enter first number: ");
    if (scanf("%d", &num1) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter second number: ");
    if (scanf("%d", &num2) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    int result = minOperations(num1, num2);
    printf("Minimum operations required: %d\n", result);
    
    return EXIT_SUCCESS;
}