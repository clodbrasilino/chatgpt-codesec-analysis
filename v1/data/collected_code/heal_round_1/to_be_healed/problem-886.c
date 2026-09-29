#include <stdio.h>

float calculateAverage(int list[], int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        sum += list[i];
    }
    return (float)sum / length;
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    int length = sizeof(list) / sizeof(list[0]);
    float average = calculateAverage(list, length);
    printf("The average is: %f\n", average);
    return 0;
}