#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 0, got 3
  *  test case 2 failed: expected 1, got 2
  */

int count_hexadecimal_numbers(unsigned long long start, unsigned long long end) {
    int count = 0;
    unsigned long long i;

    if (start > end) {
        return -1;
    }

    for (i = start; i <= end; i++) {
        count++;
        if (i == 0xFFFFFFFFFFFFFFFFULL) {
            break;
        }
    }

    return count;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:5074,execs:583,op:havoc,rep:13; likely memory-safety defect
  */

int main(void) {
    unsigned long long start, end;
    int result;

    if (scanf("%llu", &start) != 1) {
        fprintf(stderr, "Invalid input for start\n");
        return EXIT_FAILURE;
    }

    if (scanf("%llu", &end) != 1) {
        fprintf(stderr, "Invalid input for end\n");
        return EXIT_FAILURE;
    }

    result = count_hexadecimal_numbers(start, end);

    if (result < 0) {
        fprintf(stderr, "Invalid range: start must be less than or equal to end\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}