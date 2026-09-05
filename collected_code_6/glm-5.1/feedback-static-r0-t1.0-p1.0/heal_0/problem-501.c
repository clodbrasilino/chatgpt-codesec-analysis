#include <stdio.h>
#include <stdlib.h>

int find_common_divisor(int a, int b) {
    if (a == 0 && b == 0) {
        return 0;
    }

    a = abs(a);
    b = abs(b);

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

int main(void) {
    int num1 = 0;
    int num2 = 0;

    if (scanf("%d %d", &num1, &num2) != 2) {
        return 1;
    }

    int result = find_common_divisor(num1, num2);

    printf("%d\n", result);

    return 0;
}