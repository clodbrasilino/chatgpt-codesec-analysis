#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 4, got <no output>
  */

int minOperations(int a, int b) {
    int diff = abs(a - b);
    int operations = 0;

    operations += diff / 5;
    diff %= 5;

    operations += diff / 2;
    diff %= 2;

    if (diff == 1) {
        operations += 2;
    }
    
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
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}