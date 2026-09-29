#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'pow'
  */

int concatenateIntegers(const int *numbers, size_t count) {
    long result = 0;
    for (size_t i = 0; i < count; ++i) {
        int num = numbers[i];
        int length = 0;
        long temp = num;
        while (temp > 0) {
            temp /= 10;
            length++;
        }
        /* Possible weaknesses found:
         *  call to undeclared library function 'pow' with type 'double (double, double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'pow' [-Wimplicit-function-declaration]
         *  include the header <math.h> or explicitly provide a declaration for 'pow'
         */
        result *= (length ? pow(10, length) : 1);
        result += num;
    }
    return (int)result;
}

int main() {
    int numbers[] = {123, 456, 789};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int result = concatenateIntegers(numbers, count);
    printf("%d\n", result);
    return 0;
}