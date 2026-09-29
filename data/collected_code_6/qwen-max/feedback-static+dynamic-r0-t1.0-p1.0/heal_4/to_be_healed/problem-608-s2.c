#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got <no output>
  *  test case 1 failed: expected 5, got <no output>
  *  test case 0 failed: expected 2, got <no output>
  */

unsigned long long bellNumber(int n) {
    if (n < 0) return 0;
    unsigned long long *bell = (unsigned long long *)malloc((n+1) * (n+1) * sizeof(unsigned long long));
    if (bell == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memset(bell, 0, (n+1) * (n+1) * sizeof(unsigned long long));
    bell[0] = 1;
    for (int i = 1; i <= n; i++) {
        bell[i*(n+1)] = bell[(i-1)*(n+1)+(i-1)];
        for (int j = 1; j <= i; j++)
            bell[i*(n+1)+j] = bell[(i-1)*(n+1)+(j-1)] + bell[i*(n+1)+(j-1)];
    }
    unsigned long long result = bell[n*(n+1)];
    free(bell);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:792,execs:255,op:havoc,rep:5; likely memory-safety defect
  */

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[16];
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;
        int n;
        if (sscanf(input, "%d", &n) == 1 && n >= 0) {
            unsigned long long result = bellNumber(n);
            printf("The %dth Bell number is: %llu\n", n, result);
        } else {
            fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}