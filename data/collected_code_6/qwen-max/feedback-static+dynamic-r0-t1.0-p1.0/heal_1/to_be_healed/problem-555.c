#include <stdio.h>

long sum_of_cubes(int n) {
    long sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += (long)i * i * i;
    }
    return sum;
}

long sum_of_numbers(int n) {
    long sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += i;
    }
    return sum;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 6, got <no output>
  *  test case 1 failed: expected 210, got <no output>
  *  test case 0 failed: expected 30, got <no output>
  */

long difference(int n) {
    long cubes_sum = sum_of_cubes(n);
    long numbers_sum = sum_of_numbers(n);
    return cubes_sum - numbers_sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:720,execs:246,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    long diff = difference(n);
    printf("The difference is: %ld\n", diff);

    return 0;
}