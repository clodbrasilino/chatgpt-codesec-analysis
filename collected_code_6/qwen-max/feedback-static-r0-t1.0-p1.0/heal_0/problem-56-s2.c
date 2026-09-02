#include <stdio.h>

int reverse_number(int num) {
    int reversed = 0;
    while (num > 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    return reversed;
}

int is_one_less_than_twice_reverse(int n) {
    int reversed = reverse_number(n);
    return (2 * reversed - 1 == n);
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    if (is_one_less_than_twice_reverse(number)) {
        printf("The number is one less than twice its reverse.\n");
    } else {
        printf("The number is not one less than twice its reverse.\n");
    }
    return 0;
}