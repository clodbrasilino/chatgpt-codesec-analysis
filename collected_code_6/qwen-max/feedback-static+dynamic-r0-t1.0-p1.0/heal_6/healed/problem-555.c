#include <stdio.h>
#include <stdlib.h>

long sum_of_cubes(int n) {
    long sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += (long)i * i * i;
    }
    return sum;
}

long sum_of_numbers(int n) {
    long sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += i;
    }
    return sum;
}

long difference(int n) {
    if (n < 1) {
        return 0;
    }
    long cubes_sum = sum_of_cubes(n);
    long numbers_sum = sum_of_numbers(n);
    return cubes_sum - numbers_sum;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    while (1) {
        if (scanf("%d", &n) == 1 && n > 0) {
            break;
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        printf("Invalid input. Please enter a positive integer.\n");
        printf("Enter a positive integer: ");
    }

    long diff = difference(n);
    printf("The difference is: %ld\n", diff);

    return 0;
}