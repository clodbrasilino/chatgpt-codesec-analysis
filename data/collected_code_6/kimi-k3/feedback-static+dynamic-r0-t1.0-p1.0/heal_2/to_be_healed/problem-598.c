#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int isArmstrong(int num) {
    int originalNum, result = 0, n = 0;
    double tempResult = 0.0;

    originalNum = num;

    while (originalNum != 0) {
        originalNum /= 10;
        ++n;
    }

    originalNum = num;

    while (originalNum != 0) {
        int remainder = originalNum % 10;
        tempResult += pow(remainder, n);
        originalNum /= 10;
    }

    /* Possible weaknesses found:
     *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  'INT_MIN' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'INT_MIN'
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MAX' undeclared (first use in this function)
     */
    if (tempResult >= (double)INT_MAX || tempResult <= (double)INT_MIN) {
        return 0;
    }
    
    result = (int)tempResult;

    if (result == num)
        return 1;
    else
        return 0;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (isArmstrong(num))
        printf("%d is an Armstrong number.\n", num);
    else
        printf("%d is not an Armstrong number.\n", num);

    return 0;
}