#include <stdio.h>

int find_maximum(int a, int b, int c) {
    int max = a;

    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }

    return max;
}

int main(void) {
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    int result = 0;
    int read_count = 0;

    printf("Enter three integers: ");
    read_count = scanf("%d %d %d", &num1, &num2, &num3);

    if (read_count != 3) {
        printf("Invalid input.\n");
        return 1;
    }

    result = find_maximum(num1, num2, num3);

    printf("The maximum is: %d\n", result);

    return 0;
}