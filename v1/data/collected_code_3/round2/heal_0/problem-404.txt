#include <stdio.h>

int find_min(int a, int b) {
    if(a < b)
        return a;
    else
        return b;
}

int main() {
    int num1, num2, min;

    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    min = find_min(num1, num2);

    printf("Minimum is: %d\n", min);

    return 0;
}