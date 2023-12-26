#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'pow'
  */

double geometricSum(double a, double r, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  include '<math.h>' or provide a declaration of 'pow'
         *  implicit declaration of function 'pow' [-Wimplicit-function-declaration]
         *  incompatible implicit declaration of built-in function 'pow' [-Wbuiltin-declaration-mismatch]
         */
        sum += a * pow(r, i);
    }
    return sum;
}

int main() {
    double a, r;
    int n;
    printf("Enter the first term (a): ");
    /* Possible weaknesses found:
     *  Cannot determine that 'a' is initialized [premium-bughuntingUninit]
     */
    scanf("%lf", &a);
    printf("Enter the common ratio (r): ");
    /* Possible weaknesses found:
     *  Cannot determine that 'r' is initialized [premium-bughuntingUninit]
     */
    scanf("%lf", &r);
    printf("Enter the number of terms (n): ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);
    /* Possible weaknesses found:
     *  Cannot determine that 'r' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'a' is initialized [premium-bughuntingUninit]
     */
    double sum = geometricSum(a, r, n);
    printf("Sum of the geometric progression series: %lf\n", sum);
    return 0;
}