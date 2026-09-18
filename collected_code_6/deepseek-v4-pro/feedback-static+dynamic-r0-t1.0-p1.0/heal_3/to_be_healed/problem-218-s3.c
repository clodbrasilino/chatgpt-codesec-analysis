#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got 2
  *  test case 1 failed: expected 4, got 3
  *  test case 2 failed: expected 3, got 2
  */

int min_operations(int a, int b) {
    int xor_result = a ^ b;
    int count = 0;
    
    while (xor_result) {
        count++;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -2147483648 - 1 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:1672,execs:1152,op:havoc,rep:8)
         */
        xor_result &= xor_result - 1;
    }
    
    return count;
}

int main(void) {
    int num1, num2;
    
    printf("Enter first number: ");
    if (scanf("%d", &num1) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("Enter second number: ");
    if (scanf("%d", &num2) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("Minimum operations required: %d\n", min_operations(num1, num2));
    
    return 0;
}