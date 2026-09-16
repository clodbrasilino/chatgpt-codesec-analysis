#include <stdio.h>
#include <stdlib.h>

int diff_even_odd_sum(int n) {
    int even_sum = 0;
    int odd_sum = 0;
    while (n > 0) {
        int digit = n % 10;
        if (digit % 2 == 0) {
            even_sum += digit;
        } else {
            odd_sum += digit;
        }
        n /= 10;
    }
    return even_sum - odd_sum;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int result = diff_even_odd_sum(abs(number));
    printf("Difference between sum of even and odd digits: %d\n", result);
    return EXIT_SUCCESS;
}