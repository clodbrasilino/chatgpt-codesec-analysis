#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  *  test case 1 failed: expected 4, got <no output>
  */

int findFirstDigit(long num) {
    if (num < 0) num = -num;
    int digits = (int)log10(num);
    return (int)(num / pow(10, digits));
}

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);
    int firstDigit = findFirstDigit(number);
    printf("The first digit is %d\n", firstDigit);
    return 0;
}