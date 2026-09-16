#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_non_prime(int num) {
    if (num <= 1) {
        return true;
    }
    if (num == 2) {
        return false;
    }
    if (num % 2 == 0) {
        return true;
    }
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    if (is_non_prime(num)) {
        printf("%d is a non-prime number\n", num);
    } else {
        printf("%d is a prime number\n", num);
    }
    return 0;
}