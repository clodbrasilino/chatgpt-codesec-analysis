#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 3, got <no output>
  *  test case 0 failed: expected 2, got <no output>
  *  test case 2 failed: expected 51, got <no output>
  */

double average_of_evens(int n) {
    if (n <= 0 || n % 2 != 0) return 0.0;

    int sum = 0;
    int count = 0;
    for (int i = 2; i <= n; i += 2) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2147441940 + 92682 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:46,execs:34,op:havoc,rep:4)
         */
        sum += i;
        count++;
    }
    return (double)sum / count;
}

int main() {
    int n;
    printf("Enter an even number: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    double avg = average_of_evens(n);
    if (avg > 0.0) {
        printf("Average of even numbers up to %d is: %.2f\n", n, avg);
    } else {
        printf("No even numbers to calculate the average.\n");
    }
    return 0;
}