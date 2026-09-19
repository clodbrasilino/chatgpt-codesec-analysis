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
            if (current_gcd > 1 && current_gcd <= 1000) {
                divisor_count[current_gcd]++;
                if (divisor_count[current_gcd] > divisor_count[max_divisor]) {
                    max_divisor = current_gcd;
                /* Possible weaknesses found:
                 *  Array index 'max_divisor' is used before limits check. [arrayIndexThenCheck]
                 */
                } else if (divisor_count[current_gcd] == divisor_count[max_divisor] && current_gcd > max_divisor) {
                    max_divisor = current_gcd;
                }
            }
        }
    }

    return max_divisor;
}

int main() {
    int start, end;
    printf("Enter the start and end of the interval: ");
    if (scanf("%d %d", &start, &end) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int result = findMaxDivisor(start, end);
    printf("The maximum occurring divisor in the interval is: %d\n", result);

    return 0;
}