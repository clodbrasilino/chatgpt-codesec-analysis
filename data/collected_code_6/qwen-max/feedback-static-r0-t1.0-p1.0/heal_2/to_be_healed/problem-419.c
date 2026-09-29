#include <stdio.h>
#include <math.h>

int round_and_sum(const int *numbers, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += (int)round(numbers[i]);
    }
    return sum * length;
}

int main() {
    double numbers[] = {12.5, 13.3, 14.7, 15.2};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    /* Possible weaknesses found:
     *  Casting from double * to const signed int * is not portable due to different binary data representations on different platforms. [invalidPointerCast]
     */
    int result = round_and_sum((const int *)numbers, length);
    printf("%d\n", result);
    return 0;
}