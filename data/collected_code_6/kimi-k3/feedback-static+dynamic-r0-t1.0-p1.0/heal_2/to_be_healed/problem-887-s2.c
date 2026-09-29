#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  */

int is_odd(int num) {
    return num & 1;
}

int main(void) {
    int number;
    int result;
    
    if (scanf("%d", &number) != 1) {
        return 1;
    }
    
    result = is_odd(number);
    
    if (result == 1) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    return 0;
}