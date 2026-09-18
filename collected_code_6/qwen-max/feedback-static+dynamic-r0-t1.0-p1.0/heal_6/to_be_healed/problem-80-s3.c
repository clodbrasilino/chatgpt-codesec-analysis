#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

long nth_tetrahedral_number(long n) {
    /* Possible weaknesses found:
     *  Assuming that condition 'n<=0' is not redundant
     */
    if (n <= 0) return 0;
    long max_div_6 = LONG_MAX / 6;
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (n > (long)((sqrt(8.0 * (double)max_div_6 + 1.0) - 1.0) / 2.0)) {
        fprintf(stderr, "Input too large, would cause overflow.\n");
        exit(EXIT_FAILURE);
    }
    /* Possible weaknesses found:
     *  Assignment 'n1=n+1', assigned value is greater than 1
     */
    long n1 = n + 1;
    /* Possible weaknesses found:
     *  Assignment 'n2=n+2', assigned value is greater than 2
     */
    long n2 = n + 2;
    /* Possible weaknesses found:
     *  Condition 'n>0' is always true [knownConditionTrueFalse]
     *  Condition 'n1>0' is always true [knownConditionTrueFalse]
     *  Condition 'n1>0' is always true
     *  Condition 'n2>0' is always true [knownConditionTrueFalse]
     *  Condition 'n>0' is always true
     *  Condition 'n2>0' is always true
     */
    if (n > 0 && n1 > 0 && n2 > 0 && n1 < n2 && (n1 / 6) < (LONG_MAX / n2) && (n * (n1 / 6)) < (LONG_MAX / n2)) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2555555 * 6530869024692 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:17353,execs:6788,op:havoc,rep:3)
         */
        return (n * (n1 * n2)) / 6;
    } else {
        fprintf(stderr, "Calculation would cause overflow.\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }
    long result = nth_tetrahedral_number(n);
    printf("The %ldth tetrahedral number is: %ld\n", n, result);
    return 0;
}