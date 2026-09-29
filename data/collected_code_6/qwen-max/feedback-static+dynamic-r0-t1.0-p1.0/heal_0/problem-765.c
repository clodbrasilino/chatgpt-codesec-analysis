#include <stdio.h>
#include <stdbool.h>

bool is_polite_number(int n) {
    if (n == 1) return false;
    while (n % 2 == 0) n /= 2;
    return (n != 1);
}

int find_nth_polite_number(int n) {
    int count = 0;
    int number = 1;
    while (1) {
        if (is_polite_number(number)) {
            count++;
            if (count == n) {
                return number;
            }
        }
        number++;
    }
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    int nth_polite_number = find_nth_polite_number(n);
    printf("The %d-th polite number is: %d\n", n, nth_polite_number);
    return 0;
}