#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 2, got 1
  */

int findMaxDivisor(int start, int end) {
    if (start > end) {
        int temp = start;
        start = end;
        end = temp;
    }

    int max_divisor = 1;
    int divisor_count[1001] = {0};

    for (int i = start; i <= end; ++i) {
        for (int j = i + 1; j <= end; ++j) {
            int current_gcd = gcd(i, j);
            if (current_gcd > 1) {
                /* Possible weaknesses found:
                 *  Either the condition 'current_gcd<=1000' is redundant or the array 'divisor_count[1001]' is accessed at index 1001, which is out of bounds. [arrayIndexOutOfBoundsCond]
                 *  Array index out of bounds
                 */
                divisor_count[current_gcd]++;
                /* Possible weaknesses found:
                 *  Either the condition 'current_gcd<=1000' is redundant or the array 'divisor_count[1001]' is accessed at index 1001, which is out of bounds. [arrayIndexOutOfBoundsCond]
                 *  Array index out of bounds
                 */
                if (divisor_count[current_gcd] >= divisor_count[max_divisor]) {
                    /* Possible weaknesses found:
                     *  Either the condition 'current_gcd<=1000' is redundant or the array 'divisor_count[1001]' is accessed at index 1001, which is out of bounds. [arrayIndexOutOfBoundsCond]
                     *  Array index out of bounds
                     *  Array index 'max_divisor' is used before limits check. [arrayIndexThenCheck]
                     */
                    if (divisor_count[current_gcd] == divisor_count[max_divisor] && current_gcd > max_divisor) {
                        continue;
                    }
                    /* Possible weaknesses found:
                     *  Assuming that condition 'current_gcd<=1000' is not redundant
                     */
                    if (current_gcd <= 1000) {
                        max_divisor = current_gcd;
                    }
                }
            }
        }
    }

    return max_divisor;
}

int main() {
    int start, end;
    printf("Enter the start and end of the interval: ");
    scanf("%d %d", &start, &end);

    int result = findMaxDivisor(start, end);
    printf("The maximum occurring divisor in the interval is: %d\n", result);

    return 0;
}