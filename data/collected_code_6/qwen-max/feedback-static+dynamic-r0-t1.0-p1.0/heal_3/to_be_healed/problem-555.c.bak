#include <stdio.h>
#include <stdint.h>

int64_t sum_of_cubes(int n) {
    int64_t sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += (int64_t)i * i * i;
    }
    return sum;
}

int64_t sum_of_numbers(int n) {
    int64_t sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += i;
    }
    return sum;
}

int64_t difference(int n) {
    int64_t cubes_sum = sum_of_cubes(n);
    int64_t numbers_sum = sum_of_numbers(n);
    return cubes_sum - numbers_sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:269,execs:175,op:havoc,rep:9; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    int64_t diff = difference(n);
    printf("The difference is: %ld\n", diff);

    return 0;
}