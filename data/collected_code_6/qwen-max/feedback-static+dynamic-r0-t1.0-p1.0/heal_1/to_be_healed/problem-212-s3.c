#include <stdio.h>
#include <stdlib.h>

long long sum_of_fourth_powers(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += (long long)i * i * i * i;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:313,execs:175,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }

    long long result = sum_of_fourth_powers(n);
    printf("The sum of the fourth powers of the first %d natural numbers is: %lld\n", n, result);

    return EXIT_SUCCESS;
}