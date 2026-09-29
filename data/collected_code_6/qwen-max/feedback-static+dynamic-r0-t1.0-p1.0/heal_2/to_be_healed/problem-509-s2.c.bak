#include <stdio.h>
#include <stdlib.h>

double average_of_odds(int n) {
    int sum = 0, count = 0;
    for (int i = 1; i <= n; i += 2) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2147395600 + 92681 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:532,execs:238,op:havoc,rep:6)
         */
        sum += i;
        count++;
    }
    if (count == 0) return 0.0; 
    return (double)sum / count;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    double avg = average_of_odds(n);
    printf("Average of odd numbers till %d is: %.2f\n", n, avg);
    return EXIT_SUCCESS;
}