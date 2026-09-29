#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 243, got 27
  *  test case 1 failed: expected 513, got 171
  */

int round_and_sum(const double *numbers, int length) {
    int sum = 0;
    for (int i = 0; i < length; ++i) {
        sum += (int)(round(numbers[i]));
    }
    return sum;
}

int main() {
    double numbers1[] = {3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9};
    double numbers2[] = {2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9};
    int length1 = sizeof(numbers1) / sizeof(numbers1[0]);
    int length2 = sizeof(numbers2) / sizeof(numbers2[0]);

    int result1 = round_and_sum(numbers1, length1);
    int result2 = round_and_sum(numbers2, length2);

    printf("%d\n", result1);
    printf("%d\n", result2);

    return 0;
}