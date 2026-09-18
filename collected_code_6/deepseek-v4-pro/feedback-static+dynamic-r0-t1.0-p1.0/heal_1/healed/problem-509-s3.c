#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long sum_odd_numbers(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i += 2) {
        if (sum > LLONG_MAX - i) {
            return -1;
        }
        sum += i;
    }
    return sum;
}

int count_odd_numbers(int n) {
    return (n + 1) / 2;
}

float average_of_odd_numbers(int n) {
    if (n <= 0 || n % 2 == 0) {
        return -1.0f;
    }
    long long sum = sum_odd_numbers(n);
    if (sum < 0) {
        return -1.0f;
    }
    int count = count_odd_numbers(n);
    return (float)sum / count;
}

int main(void) {
    int n;
    printf("Enter an odd number: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    float avg = average_of_odd_numbers(n);
    if (avg < 0) {
        printf("Please enter a positive odd number\n");
        return 1;
    }
    printf("Average of odd numbers up to %d: %.2f\n", n, avg);
    return 0;
}