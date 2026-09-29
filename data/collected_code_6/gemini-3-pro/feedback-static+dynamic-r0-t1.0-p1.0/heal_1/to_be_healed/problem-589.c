#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void find_perfect_squares(int num1, int num2) {
    int start = (num1 < num2) ? num1 : num2;
    int end = (num1 > num2) ? num1 : num2;

    if (start < 0) {
        start = 0;
    }

    int start_sqrt = (int)ceil(sqrt((double)start));
    /* Possible weaknesses found:
     * UBSan: nan is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000004,time:49751,execs:24800,op:havoc,rep:2)
     */
    int end_sqrt = (int)floor(sqrt((double)end));

    for (int i = start_sqrt; i <= end_sqrt; i++) {
        printf("%d\n", i * i);
    }
}

int main(void) {
    int num1, num2;

    if (scanf("%d %d", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    find_perfect_squares(num1, num2);

    return EXIT_SUCCESS;
}