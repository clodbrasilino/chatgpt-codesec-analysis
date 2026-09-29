#include <stdio.h>
#include <stdlib.h>

int find_last_digit(int number) {
    int absolute_value = abs(number);
    return absolute_value % 10;
}

int main() {
    int number;
    if (scanf("%d", &number) == 1) {
        int last_digit = find_last_digit(number);
        printf("%d\n", last_digit);
        return 0;
    }
    return 1;
}