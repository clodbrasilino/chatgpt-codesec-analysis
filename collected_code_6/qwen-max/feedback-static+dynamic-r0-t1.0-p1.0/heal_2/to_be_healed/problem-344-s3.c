#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool isPerfectSquare(int n) {
    int root = (int)sqrt(n);
    return n == root * root;
}

int countNumbersWithOddFactors(int start, int end) {
    int count = 0;
    for (int i = start; i <= end; ++i) {
        if (isPerfectSquare(i)) {
            count++;
        }
    }
    return count;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:70,execs:46,op:havoc,rep:5; likely memory-safety defect
  */

int main() {
    int start, end;
    printf("Enter the range (start end): ");
    scanf("%d %d", &start, &end);

    int result = countNumbersWithOddFactors(start, end);
    printf("Numbers with odd factors in the range: %d\n", result);

    return 0;
}