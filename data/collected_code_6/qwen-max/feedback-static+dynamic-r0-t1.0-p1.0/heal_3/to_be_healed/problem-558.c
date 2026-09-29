#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int abs_diff(int a, int b) {
    return a > b ? a - b : b - a;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 6, got <no output>
  *  test case 2 failed: expected 7, got <no output>
  */

int digit_distance(int num1, int num2) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s1[12], s2[12];
    snprintf(s1, sizeof(s1), "%d", num1);
    snprintf(s2, sizeof(s2), "%d", num2);

    size_t len1 = strnlen(s1, sizeof(s1));
    size_t len2 = strnlen(s2, sizeof(s2));
    size_t max_len = (len1 > len2) ? len1 : len2;

    int distance = 0;
    for (size_t i = 0; i < max_len; ++i) {
        int d1 = (i < len1) ? s1[i] - '0' : 0;
        int d2 = (i < len2) ? s2[i] - '0' : 0;
        distance += abs_diff(d1, d2);
    }
    return distance;
}

int main() {
    int num1 = 234;
    int num2 = 489;
    printf("The digit distance between %d and %d is: %d\n", num1, num2, digit_distance(num1, num2));
    return 0;
}