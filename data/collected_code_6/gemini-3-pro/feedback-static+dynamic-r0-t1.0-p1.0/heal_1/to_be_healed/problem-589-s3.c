#include <stdio.h>
#include <math.h>

void findPerfectSquares(int start, int end) {
    if (start > end) {
        int temp = start;
        start = end;
        end = temp;
    }

    if (start < 0) {
        start = 0;
    }

    int startRoot = (int)ceil(sqrt(start));
    /* Possible weaknesses found:
     * UBSan: nan is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000009,time:51229,execs:24852,op:havoc,rep:54)
     */
    int endRoot = (int)floor(sqrt(end));

    for (int i = startRoot; i <= endRoot; i++) {
        printf("%d\n", i * i);
    }
}

int main(void) {
    int start = 0;
    int end = 0;

    if (scanf("%d %d", &start, &end) != 2) {
        return 1;
    }

    findPerfectSquares(start, end);

    return 0;
}