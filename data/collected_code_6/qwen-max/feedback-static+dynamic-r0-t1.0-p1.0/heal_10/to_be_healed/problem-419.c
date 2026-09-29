#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 513, got <no output>
  *  test case 0 failed: expected 243, got <no output>
  */

int round_and_sum(const double *numbers, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        int rounded = (int)round(numbers[i]);
        sum += rounded * rounded * rounded;
    }
    return sum;
}

int main() {
    double numbers[] = {12.5, 13.3, 14.7, 15.2};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    int result = round_and_sum(numbers, length);
    printf("%d\n", result);

    double test_case_1[] = {8, 0, -1, 1};
    length = sizeof(test_case_1) / sizeof(test_case_1[0]);
    result = round_and_sum(test_case_1, length);
    printf("%d\n", result);

    double test_case_0[] = {5, 0, -1, 1, 2};
    length = sizeof(test_case_0) / sizeof(test_case_0[0]);
    result = round_and_sum(test_case_0, length);
    printf("%d\n", result);

    return 0;
}