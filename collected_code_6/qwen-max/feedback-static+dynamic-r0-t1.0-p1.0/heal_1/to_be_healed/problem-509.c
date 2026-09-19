#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 3, got <no output>
  *  test case 2 failed: expected 6, got <no output>
  *  test case 0 failed: expected 5, got <no output>
  */

double average_of_odds(int n) {
    int sum = 0, count = 0;
    for (int i = 1; i <= n; i += 2) {
        sum += i;
        count++;
    }
    return (count == 0) ? 0.0 : (double)sum / count;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:38,execs:34,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter an odd number: ");
    scanf("%d", &n);

    if (n % 2 != 0) {
        double avg = average_of_odds(n);
        printf("Average of odd numbers till %d is: %.2f\n", n, avg);
    } else {
        printf("Please enter a valid odd number.\n");
    }

    return 0;
}