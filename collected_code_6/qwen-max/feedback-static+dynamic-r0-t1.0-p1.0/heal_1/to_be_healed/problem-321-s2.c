#include <stdio.h>
#include <stdlib.h>

long long calculateDemloNumber(int n) {
    long long result = 0;
    int multiplier = 1;
    for (int i = n; i > 0; i--) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2 * 1111111111 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:19,execs:13,op:havoc,rep:2)
         */
        result += (i * multiplier);
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1111111111 * 10 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:19,execs:13,op:havoc,rep:2)
         */
        multiplier = multiplier * 10 + 1;
    }
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000000,time:10624,execs:4145,op:havoc,rep:6; likely memory-safety defect
  */

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1 || number <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    long long demloNumber = calculateDemloNumber(number);
    printf("The Demlo number of %d is %lld\n", number, demloNumber);
    return EXIT_SUCCESS;
}