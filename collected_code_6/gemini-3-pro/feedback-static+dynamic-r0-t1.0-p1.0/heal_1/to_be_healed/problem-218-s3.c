#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got 2
  *  test case 0 failed: expected 1, got 3
  *  test case 1 failed: expected 4, got 3
  */

int min_operations(int num1, int num2) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -2072745074 - 1468588942 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:27756,execs:12913,op:havoc,rep:2)
     */
    int diff = abs(num1 - num2);
    int steps = 0;
    int current_sum = 0;

    while (current_sum < diff || (current_sum - diff) % 2 != 0) {
        steps++;
        current_sum += steps;
    }

    return steps;
}

int main(void) {
    int num1, num2;
    
    if (scanf("%d %d", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int result = min_operations(num1, num2);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}