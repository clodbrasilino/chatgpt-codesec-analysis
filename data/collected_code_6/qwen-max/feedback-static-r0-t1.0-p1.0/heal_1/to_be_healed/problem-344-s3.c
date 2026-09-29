#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'sqrt'
  */

bool isPerfectSquare(int n) {
    /* Possible weaknesses found:
     *  include the header <math.h> or explicitly provide a declaration for 'sqrt'
     *  implicit declaration of function 'sqrt' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'sqrt' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    int root = (int)sqrt(n);
    return n == root * root;
}

int countNumbersWithOddFactors(int start, int end) {
    int count = 0;
    for (int i = start; i <= end; ++i) {
        if (isPerfectSquare(i)) {
            count++;
        }
    }
    return count;
}

int main() {
    int start, end;
    printf("Enter the range (start end): ");
    scanf("%d %d", &start, &end);

    int result = countNumbersWithOddFactors(start, end);
    printf("Numbers with odd factors in the range: %d\n", result);

    return 0;
}