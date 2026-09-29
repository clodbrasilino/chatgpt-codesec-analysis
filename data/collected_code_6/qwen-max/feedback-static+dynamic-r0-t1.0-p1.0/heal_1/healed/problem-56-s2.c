#include <stdio.h>
#include <limits.h>

long long reverse_number(int num) {
    long long reversed = 0;
    while (num != 0) {
        if (reversed > LONG_MAX / 10 || (reversed == LONG_MAX / 10 && num % 10 > 7)) return -1;
        if (reversed < LONG_MIN / 10 || (reversed == LONG_MIN / 10 && num % 10 < -8)) return -1;
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    return reversed;
}

int is_one_less_than_twice_reverse(int n) {
    long long reversed = reverse_number(n);
    if (reversed == -1) return 0;
    long long twice_reversed = 2 * reversed;
    if (twice_reversed > INT_MAX || twice_reversed < INT_MIN) return 0;
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