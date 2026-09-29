#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

bool is_valid_input(int n) {
    return n > 0 && (long long)n * n * n <= LLONG_MAX;
}

long long cube_sum(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        if (!is_valid_input(i)) {
            fprintf(stderr, "Input too large, causing overflow.\n");
            exit(EXIT_FAILURE);
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223193340756366400 + 473384830201856 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1569,execs:703,op:havoc,rep:5)
         */
        sum += (long long)i * i * i;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:984,execs:442,op:havoc,rep:7; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || !is_valid_input(n)) {
        fprintf(stderr, "Invalid input. Please enter a smaller positive integer.\n");
        return EXIT_FAILURE;
    }

    long long result = cube_sum(n);
    printf("Cube sum of first %d natural numbers is: %lld\n", n, result);

    return EXIT_SUCCESS;
}