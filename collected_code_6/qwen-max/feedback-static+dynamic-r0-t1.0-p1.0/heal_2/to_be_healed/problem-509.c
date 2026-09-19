#include <stdio.h>
#include <stdlib.h>

double average_of_odds(int n) {
    int sum = 0, count = 0;
    for (int i = 1; i <= n; i += 2) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2147395600 + 92681 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:256,execs:239,op:havoc,rep:2)
         */
        sum += i;
        count++;
    }
    return (count == 0) ? 0.0 : (double)sum / count;
}

int main() {
    int n;
    printf("Enter an odd number: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input. Please enter a valid integer.\n");
        return EXIT_FAILURE;
    }

    if (n % 2 != 0) {
        double avg = average_of_odds(n);
        printf("Average of odd numbers till %d is: %.2f\n", n, avg);
    } else {
        printf("Please enter a valid odd number.\n");
    }

    return 0;
}