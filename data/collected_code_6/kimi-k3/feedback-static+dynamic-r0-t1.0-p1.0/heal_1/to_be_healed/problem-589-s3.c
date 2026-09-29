#include <stdio.h>
#include <math.h>

void findPerfectSquares(int start, int end) {
    int i;
    int sqrtStart = (int)sqrt(start);
    int sqrtEnd = (int)sqrt(end);
    
    if (sqrtStart * sqrtStart < start) {
        sqrtStart++;
    }
    
    for (i = sqrtStart; i <= sqrtEnd; i++) {
        printf("%d ", i * i);
    }
    printf("\n");
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:5251,execs:2084,op:havoc,rep:12; likely memory-safety defect
  */

int main() {
    int start, end;
    
    printf("Enter the starting number: ");
    if (scanf("%d", &start) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("Enter the ending number: ");
    if (scanf("%d", &end) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (start > end) {
        printf("Invalid range\n");
        return 1;
    }
    
    printf("Perfect squares between %d and %d: ", start, end);
    findPerfectSquares(start, end);
    
    return 0;
}