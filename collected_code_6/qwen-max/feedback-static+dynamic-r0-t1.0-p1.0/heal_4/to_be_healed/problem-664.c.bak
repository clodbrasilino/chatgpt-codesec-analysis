#include <stdio.h>

double average_of_evens(int n) {
    if (n <= 1) return 0.0;

    int sum = 0;
    int count = 0;
    for (int i = 2; i <= n; i += 2) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2147441940 + 92682 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:405,execs:168,op:havoc,rep:3)
         */
        sum += i;
        count++;
    }
    return (double)sum / count;
}

int main() {
    int n;
    printf("Enter an integer: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    double avg = average_of_evens(n);
    if (avg > 0.0 && n > 1) {
        printf("Average of even numbers up to %d is: %.2f\n", n, avg);
    } else {
        printf("No even numbers to calculate the average.\n");
    }
    return 0;
}