#include <stdio.h>
#include <stdlib.h>

int nth_carol_number(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: n must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    return (1 << n) - 1;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:355,execs:184,op:havoc,rep:6; likely memory-safety defect
  */

int main(void) {
    int n;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    int result = nth_carol_number(n);
    printf("The %dth Carol number is: %d\n", n, result);

    return EXIT_SUCCESS;
}