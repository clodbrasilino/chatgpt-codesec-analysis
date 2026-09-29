#include <stdio.h>
#include <math.h>

void findPerfectSquares(int start, int end) {
    for (int i = start; i <= end; ++i) {
        int sqrtVal = sqrt(i);
        if (sqrtVal * sqrtVal == i) {
            printf("%d ", i);
        }
    }
    printf("\n");
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:963,execs:411,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int start, end;
    printf("Enter the starting number: ");
    scanf("%d", &start);
    printf("Enter the ending number: ");
    scanf("%d", &end);

    findPerfectSquares(start, end);

    return 0;
}