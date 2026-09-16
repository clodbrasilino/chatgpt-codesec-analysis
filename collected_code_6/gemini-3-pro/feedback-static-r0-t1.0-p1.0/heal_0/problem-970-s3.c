#include <stdio.h>

int find_minimum(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

int main(void) {
    int num1 = 10;
    int num2 = 25;
    int min_val = 0;

    min_val = find_minimum(num1, num2);

    printf("The minimum of %d and %d is %d\n", num1, num2, min_val);

    return 0;
}