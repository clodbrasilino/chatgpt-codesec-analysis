#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t sum_of_cubes_minus_sum(int n) {
    if (n < 1) {
        return 0;
    }
    if (n > 28783) {
        int64_t sum = (int64_t)n * (n + 1) / 2;
        int64_t sum_cubes = 0;
        for (int i = 1; i <= n; i++) {
            sum_cubes += (int64_t)i * i * i;
        }
        return sum_cubes - sum;
    }
    int64_t sum = (int64_t)n * (n + 1) / 2;
    int64_t sum_cubes = sum * sum;
    return sum_cubes - sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:189,execs:139,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    printf("%" PRId64 "\n", sum_of_cubes_minus_sum(n));
    return 0;
}