#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 4, got <no output>
  */

int minOperations(int a, int b) {
    if (a == b) {
        return 0;
    }
    
    int diff = abs(a - b);
    int operations = 0;
    
    operations += diff / 5;
    diff %= 5;
    
    operations += diff / 2;
    diff %= 2;
    
    if (diff == 1) {
        operations += 2;
        /* Possible weaknesses found:
         *  Assuming that condition 'operations>1' is not redundant
         *  Condition 'operations>=2' is always true [knownConditionTrueFalse]
         *  Condition 'operations>=2' is always true
         *  Modulo of one is always equal to zero [moduloofone]
         */
        if (operations > 1 && (operations - 2) % 1 == 0 && operations >= 2) {
            operations--;
        }
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
    printf("Minimum operations required: %d\n", result);
    
    return EXIT_SUCCESS;
}