#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 56.0, got <no output>
  *  test case 0 failed: expected 35.0, got <no output>
  *  test case 2 failed: expected 84.0, got <no output>
  */

long nth_tetrahedral_number(long n) {
    if (n <= 0) return 0;
    long max_div_6 = LONG_MAX / 6;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 8 * 1537228672809129301 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000000,time:175,execs:79,op:havoc,rep:13)
     * UBSan: nan is outside the range of representable values of type 'long' (AFL crash: id:000000,sig:06,src:000000,time:175,execs:79,op:havoc,rep:13)
     */
    if (n > (long)((sqrt(8 * max_div_6 + 1) - 1) / 2)) {
        fprintf(stderr, "Input too large, would cause overflow.\n");
        exit(EXIT_FAILURE);
    }
    return n * (n + 1) * (n + 2) / 6;
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