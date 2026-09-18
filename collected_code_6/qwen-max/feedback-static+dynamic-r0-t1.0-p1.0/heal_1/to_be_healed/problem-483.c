#include <stdio.h>
#include <stdlib.h>

unsigned long long factorial(unsigned int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

unsigned int find_number_divisible_by_x(unsigned int x) {
    unsigned int i = 1;
    while (1) {
        unsigned long long fact = factorial(i);
        if (fact % x == 0) {
            return i;
        }
        i++;
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:336,execs:160,op:havoc,rep:4; likely memory-safety defect
  */

int main() {
    unsigned int x;
    printf("Enter a number: ");
    if (scanf("%u", &x) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    unsigned int result = find_number_divisible_by_x(x);
    printf("The first natural number whose factorial is divisible by %u is: %u\n", x, result);
    return EXIT_SUCCESS;
}