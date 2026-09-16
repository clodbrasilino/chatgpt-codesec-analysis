#include <stdio.h>
#include <stdlib.h>

double find_average_even(int n) {
    if (n <= 0 || n % 2 != 0) {
        return 0.0;
    }

    int count = n / 2;
    if (count <= 0) {
        return 0.0;
    }

    long long sum = 0;
    for (int i = 2; i <= n; i += 2) {
        sum += i;
    }

    return (double)sum / count;
}

int main(int argc, char * const argv[]) {
    int num;

    if (argc != 2) {
        return 1;
    }

    num = atoi(argv[1]);

    if (num <= 0 || num % 2 != 0) {
        return 1;
    }

    double avg = find_average_even(num);
    printf("%.2f\n", avg);

    return 0;
}