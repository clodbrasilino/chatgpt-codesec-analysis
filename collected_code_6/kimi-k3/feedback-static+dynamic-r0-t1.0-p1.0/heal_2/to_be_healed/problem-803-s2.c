#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected False, got <no output>
  */

bool is_perfect_square(long long num)
{
    if (num < 0) {
        return false;
    }
    
    if (num == 0 || num == 1) {
        return true;
    }
    
    long long root = (long long)sqrt((double)num);
    
    while (root * root > num) {
        root--;
    }
    
    while ((root + 1) * (root + 1) <= num) {
        root++;
    }
    
    return (root * root == num);
}

int main(void)
{
    long long num;
    
    if (scanf("%lld", &num) != 1) {
        return 1;
    }
    
    if (is_perfect_square(num)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    return 0;
}