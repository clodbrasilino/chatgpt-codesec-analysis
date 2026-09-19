#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int isArmstrong(int num) {
    int originalNum, n = 0;
    double result = 0;

    if (num < 0) {
        return 0;
    }

    originalNum = num;

    while (originalNum != 0) {
        originalNum /= 10;
        ++n;
    }

    originalNum = num;

    while (originalNum != 0) {
        int remainder = originalNum % 10;
        result += pow(remainder, n);
        originalNum /= 10;
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MIN' undeclared (first use in this function)
     *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'INT_MIN'
     *  'INT_MAX' undeclared (first use in this function)
     */
    if (result > (double)INT_MAX || result < (double)INT_MIN) {
        return 0;
    }

    if ((int)result == num)
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