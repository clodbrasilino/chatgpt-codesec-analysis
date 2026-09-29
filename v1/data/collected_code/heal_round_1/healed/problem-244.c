#include <stdio.h>

int nextPerfectSquare(int num) {
    int i = 0;
    while (1) {
        i++;
        if (i * i > num) {
            return i * i;
        }
    }
    return 0;
}

int main() {
    int num = 0;
    printf("Enter a number: ");
    scanf("%d", &num);
    int nextSquare = nextPerfectSquare(num);
    printf("Next perfect square greater than %d is %d\n", num, nextSquare);
    return 0;
}