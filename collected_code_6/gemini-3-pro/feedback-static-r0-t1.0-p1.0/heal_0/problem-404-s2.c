#include <stdio.h>

int find_min(int a, int b);

int main(void) {
    int num1;
    int num2;
    int min_value;

    if (scanf("%d %d", &num1, &num2) != 2) {
        return 1;
    }

    min_value = find_min(num1, num2);
    printf("%d\n", min_value);

    return 0;
}

int find_min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}