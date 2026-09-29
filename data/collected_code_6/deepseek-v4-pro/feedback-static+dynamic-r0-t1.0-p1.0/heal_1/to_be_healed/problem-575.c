#include <stdio.h>
#include <stdlib.h>

int find_nth_non_multiple(int n, int k) {
    /* Possible weaknesses found:
     *  Assuming that condition 'k<=0' is not redundant
     */
    if (n <= 0 || k <= 0) {
        return -1;
    }
    /* Possible weaknesses found:
     *  Division by zero
     *  Either the condition 'k<=0' is redundant or there is division by zero at line 8. [zerodivcond]
     * UBSan: signed integer overflow: 2062812956 + 687604318 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000005,time:8957,execs:4515,op:havoc,rep:4)
     */
    return n + (n - 1) / (k - 1);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:208,execs:127,op:havoc,rep:3; likely memory-safety defect
  */

int main(void) {
    int n, k, result;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter k: ");
    if (scanf("%d", &k) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = find_nth_non_multiple(n, k);
    if (result == -1) {
        fprintf(stderr, "Invalid arguments\n");
        return EXIT_FAILURE;
    }

    printf("The %d-th number not divisible by %d is: %d\n", n, k, result);

    return EXIT_SUCCESS;
}