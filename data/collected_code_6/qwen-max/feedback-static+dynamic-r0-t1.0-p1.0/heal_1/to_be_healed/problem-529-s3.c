#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 17, got <no output>
  *  test case 0 failed: expected 31, got <no output>
  *  test case 1 failed: expected 5, got <no output>
  */

int nth_jacobsthal_lucas(int n) {
    if (n == 0) return 2;
    if (n == 1) return 1;

    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    int a = 2, b = 1, c;
    for (int i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2 * -1896549735 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:391,execs:176,op:havoc,rep:6)
         * UBSan: signed integer overflow: 411503397 + 1986914164 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:391,execs:176,op:havoc,rep:6)
         */
        c = a + 2 * b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return EXIT_FAILURE;
    }

    int result = nth_jacobsthal_lucas(n);
    printf("The %dth Jacobsthal-Lucas number is: %d\n", n, result);

    return EXIT_SUCCESS;
}