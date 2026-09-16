#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int gcd(int a, int b)
{
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    
    return a;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  */

int is_coprime(int a, int b)
{
    if (a == 0 && b == 0) {
        return 0;
    }
    
    return gcd(a, b) == 1;
}

int main(void)
{
    int num1, num2;
    
    if (scanf("%d %d", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (is_coprime(num1, num2)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    return EXIT_SUCCESS;
}