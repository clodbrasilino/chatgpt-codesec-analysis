#include <stdio.h>
#include <math.h>

void findPerfectSquares(int start, int end) {
    if (start > end) {
        int temp = start;
        start = end;
        end = temp;
    }

    int first = (int)ceil(sqrt((double)start));
    int last = (int)floor(sqrt((double)end));

    if (first > last) {
        printf("No perfect squares found.\n");
        return;
    }

    for (int i = first; i <= last; i++) {
        printf("%d\n", i * i);
    }
}

int main(void) {
    int num1, num2;

    printf("Enter two numbers: ");
    if (scanf("%d %d", &num1, &num2) != 2) {
        printf("Invalid input.\n");
        return 1;
    }

    findPerfectSquares(num1, num2);

    return 0;
}