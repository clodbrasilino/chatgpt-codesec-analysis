#include <stdio.h>
#include <math.h>

void findPerfectSquares(int start, int end) {
    if (start > end) {
        printf("Invalid range\n");
        return;
    }

    int first = (int)ceil(sqrt(start));
    int last = (int)floor(sqrt(end));
    int found = 0;

    for (int i = first; i <= last; i++) {
        int square = i * i;
        if (square >= start && square <= end) {
            if (found) {
                printf(" ");
            }
            printf("%d", square);
            found = 1;
        }
    }

    if (!found) {
        printf("No perfect squares found");
    }
    printf("\n");
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:7483,execs:3300,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    int num1, num2;

    printf("Enter first number: ");
    if (scanf("%d", &num1) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    printf("Enter second number: ");
    if (scanf("%d", &num2) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    findPerfectSquares(num1, num2);

    return 0;
}