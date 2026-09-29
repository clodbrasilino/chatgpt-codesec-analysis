#include <stdio.h>
#include <math.h>

/* Possible weaknesses found:
 *  Parameter 'numbers' can be declared as pointer to const [constParameterPointer]
 */
int round_and_sum(int *numbers, int length) {
    int sum = 0;
    for(int i = 0; i < length; ++i) {
        sum += (int)round(numbers[i]);
    }
    return sum * length;
}

int main() {
    int numbers[] = {1.5, 2.3, 3.7, 4.1, 5.6};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    int result = round_and_sum(numbers, length);
    printf("%d\n", result);
    return 0;
}