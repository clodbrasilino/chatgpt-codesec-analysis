#include <stdio.h>
#include <stdint.h>

uint64_t sum_of_fifth_powers(int n) {
    uint64_t sum = 0;
    int i = 1;
    while (n > 0) {
        int even_number = 2 * i;
        sum += (uint64_t)even_number * even_number * even_number * even_number * even_number;
        i++;
        n--;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    uint64_t result = sum_of_fifth_powers(n);
    printf("The sum of the fifth powers of the first %d even natural numbers is: %llu\n", n, result);
    return 0;
}