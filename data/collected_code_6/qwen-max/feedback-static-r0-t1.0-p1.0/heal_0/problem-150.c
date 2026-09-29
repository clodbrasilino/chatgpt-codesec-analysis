#include <stdio.h>
#include <stdbool.h>

bool is_in_sequence(long long num) {
    long long a = 0, b = 1;
    while (a <= num) {
        if (a == num) return true;
        long long next = a + b;
        a = b;
        b = next;
    }
    return false;
}

int main() {
    long long n;
    printf("Enter a number: ");
    if (scanf("%lld", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if (is_in_sequence(n)) {
        printf("The number is in the sequence.\n");
    } else {
        printf("The number is not in the sequence.\n");
    }
    return 0;
}