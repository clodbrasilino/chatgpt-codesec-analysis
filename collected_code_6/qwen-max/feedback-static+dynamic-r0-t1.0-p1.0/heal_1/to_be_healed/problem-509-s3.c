#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 3, got <no output>
  *  test case 2 failed: expected 6, got <no output>
  *  test case 0 failed: expected 5, got <no output>
  */

double average_of_odds(int n) {
    if (n % 2 == 0 || n < 1) return 0.0;

    int sum = 0;
    for (int i = 1; i <= n; i += 2) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2147395600 + 92681 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:312,execs:166,op:havoc,rep:6)
         */
        sum += i;
    }
    return (double)sum / ((n + 1) / 2);
}

int main() {
    int n;
    printf("Enter an odd number: ");
    scanf("%d", &n);

    double avg = average_of_odds(n);
    if (avg > 0.0) {
        printf("The average of odd numbers up to %d is: %.2f\n", n, avg);
    } else {
        printf("Invalid input. Please enter an odd positive integer.\n");
    }

    return 0;
}