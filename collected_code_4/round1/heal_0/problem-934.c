#include <stdio.h>

long delannoy(int n, int m) {
    if ((n == 0) || (m == 0)) {
        return 1;
    }
    else {
        return delannoy(n-1, m) + delannoy(n-1, m-1) + delannoy(n, m-1);
    }
}

int main() {
    int number;

    printf("Enter a number: ");
    scanf("%d", &number);

    printf("The %d-th Delannoy number is: %ld\n", number, delannoy(number, number));

    return 0;
}