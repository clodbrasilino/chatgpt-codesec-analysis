#include <stdio.h>
#include <stdlib.h>

int sum_of_odd_factors(int n) {
    int sum = 0;
    if (n <= 0) {
        return 0;
    }
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i % 2 != 0) {
                sum += i;
            }
            if ((n / i) % 2 != 0 && (n / i) != i) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 1954764121 + 651588039 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:3146,execs:1306,op:havoc,rep:6)
                 */
                sum += (n / i);
            }
        }
    }
    return sum;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return EXIT_FAILURE;
    }
    int result = sum_of_odd_factors(number);
    printf("Sum of odd factors: %d\n", result);
    return EXIT_SUCCESS;
}