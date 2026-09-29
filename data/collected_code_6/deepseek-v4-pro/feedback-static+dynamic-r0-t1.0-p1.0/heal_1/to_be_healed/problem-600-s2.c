#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected False, got <no output>
  */

int is_even(int number) {
    return (number & 1) == 0;
}

int main(void) {
    int num;
    
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (is_even(num)) {
        printf("%d is even\n", num);
    } else {
        printf("%d is odd\n", num);
    }
    
    return 0;
}