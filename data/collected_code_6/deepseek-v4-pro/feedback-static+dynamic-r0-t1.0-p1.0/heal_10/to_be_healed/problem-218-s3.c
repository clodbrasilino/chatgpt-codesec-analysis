#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got 2
  *  test case 1 failed: expected 4, got 3
  *  test case 2 failed: expected 3, got 2
  */

int min_operations(int a, int b) {
    int count = 0;
    
    if (a == b) return 0;
    
    while (a != 0 || b != 0) {
        if ((a & 1) != (b & 1)) {
            count++;
        }
        a >>= 1;
        b >>= 1;
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