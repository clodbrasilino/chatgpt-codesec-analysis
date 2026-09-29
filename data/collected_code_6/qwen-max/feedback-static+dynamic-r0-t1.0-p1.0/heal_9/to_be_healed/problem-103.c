#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 26, got 0
  *  test case 0 failed: expected 4, got 0
  *  test case 1 failed: expected 11, got 0
  */

int64_t eulerian_number(int n, int m) {
    if (n == 0 && m == 0)
        return 1;
    /* Possible weaknesses found:
     *  Assuming that condition 'm>=n' is not redundant
     */
    if (m >= n || n < 0 || m < 0)
        return 0;
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (n > 63 || m > 63) {
        fprintf(stderr, "Input values are too large\n");
        exit(EXIT_FAILURE);
    }

    int64_t part1 = 0;
    int64_t part2 = 0;

    /* Possible weaknesses found:
     *  Condition 'n-m==0' is always false
     *  Condition 'n-m==0' is always false [knownConditionTrueFalse]
     */
    if (n - 1 == 0 || n - m == 0 || eulerian_number(n - 1, m - 1) > INT64_MAX / (n - m))
        return 0;
    part1 = (int64_t)(n - m) * eulerian_number(n - 1, m - 1);

    if (n - 1 == 0 || m + 1 == 0 || eulerian_number(n - 1, m) > INT64_MAX / (m + 1))
        return 0;
    part2 = (int64_t)(m + 1) * eulerian_number(n - 1, m);

    if (part1 > INT64_MAX - part2 || part2 > INT64_MAX - part1 || part1 < INT64_MIN + part2 || part2 < INT64_MIN + part1) {
        fprintf(stderr, "Integer overflow detected\n");
        exit(EXIT_FAILURE);
    }

    return part1 + part2;
}

int main() {
    int n, m;
    printf("Enter values for n and m: ");
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (n == 0 && m == 0) {
        printf("Eulerian number A(0, 0) is: 1\n");
        return EXIT_SUCCESS;
    }
    if (m >= n || n < 0 || m < 0) {
        printf("Eulerian number A(%d, %d) is: 0\n", n, m);
        return EXIT_SUCCESS;
    }
    int64_t result = eulerian_number(n, m);
    printf("Eulerian number A(%d, %d) is: %" PRId64 "\n", n, m, result);
    return EXIT_SUCCESS;
}