#include <stdio.h>
#include <stdbool.h>

bool is_polite_number(int n) {
    int count = 0;
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) {
            count++;
        }
    }
    return (count & (count + 1)) != 0;
}

int nth_polite_number(int n) {
    int count = 0;
    int num = 1;
    while (1) {
        if (is_polite_number(num)) {
            count++;
            if (count == n) {
                return num;
            }
        }
        num++;
    }
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) == 1 && n > 0) {
        int result = nth_polite_number(n);
        printf("The %dth polite number is: %d\n", n, result);
    } else {
        printf("Invalid input.\n");
    }
    return 0;
}