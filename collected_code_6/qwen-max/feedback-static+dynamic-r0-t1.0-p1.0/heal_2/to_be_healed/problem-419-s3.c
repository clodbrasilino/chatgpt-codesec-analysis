#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 513, got <no output>
  *  test case 0 failed: expected 243, got <no output>
  */

int round_and_sum(const int *numbers, int length) {
    int sum = 0;
    for (int i = 0; i < length; ++i) {
        sum += (int)round(numbers[i]);
    }
    return sum;
}

int main() {
    double numbers[] = {1.5, 2.3, 3.7, 4.1, 5.6};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    /* Possible weaknesses found:
     *  Casting from double * to const signed int * is not portable due to different binary data representations on different platforms. [invalidPointerCast]
     */
    int result = round_and_sum((const int *)numbers, length);
    printf("%d\n", result);
    return 0;
}