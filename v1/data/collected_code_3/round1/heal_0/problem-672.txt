#include <stdio.h>

int max_of_three(int num1, int num2, int num3) {
    int max = num1;

    if (num2 > max) {
        max = num2;
    }
    if (num3 > max) {
        max = num3;
    }

    return max;
}

int main() {
    int a = 10, b = 20, c = 30;
    int max = max_of_three(a, b, c);

    printf("Max number is: %d\n", max);

    return 0;
}