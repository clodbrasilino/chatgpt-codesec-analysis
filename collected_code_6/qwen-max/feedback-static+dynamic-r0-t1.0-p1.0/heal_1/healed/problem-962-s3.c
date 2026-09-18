#include <stdio.h>
#include <stdint.h>

int64_t sum_even_numbers(int64_t l, int64_t r) {
    if (l > r) return 0;
    int64_t sum = 0;
    if (l % 2 != 0) l++;
    for (int64_t i = l; i <= r; i += 2) {
        sum += i;
    }
    return sum;
}

int main() {
    int64_t l, r;
    printf("Enter the range (l and r): ");
    if (scanf("%ld %ld", &l, &r) != 2) {
        printf("Invalid input.\n");
        return 1;
    }
    int64_t result = sum_even_numbers(l, r);
    printf("Sum of all even numbers between %ld and %ld is: %ld\n", l, r, result);
    return 0;
}