#include <stdio.h>
#include <stdlib.h>

int sum_odd_numbers(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i += 2) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2147395600 + 92681 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:1149,execs:596,op:havoc,rep:3)
         */
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
    int sum = sum_odd_numbers(n);
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