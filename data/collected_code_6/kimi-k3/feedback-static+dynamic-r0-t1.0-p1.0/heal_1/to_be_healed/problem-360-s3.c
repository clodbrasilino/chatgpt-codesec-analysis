#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long carol_number(int n)
{
    if (n <= 0) {
        return -1;
    }
    if (n > 62) {
        return -1;
    }
    long long power = 1LL << n;
    long long result = (power - 1) * (power - 1) - 2;
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000004,time:5844,execs:2467,op:havoc,rep:4; likely memory-safety defect
  */

int main(void)
{
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    long long result = carol_number(n);
    if (result == -1) {
        fprintf(stderr, "Invalid n or overflow would occur\n");
        return EXIT_FAILURE;
    }
    printf("Carol number %d: %lld\n", n, result);
    return EXIT_SUCCESS;
}