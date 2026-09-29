#include <stdio.h>
#include <stdlib.h>

int sumAlternateChains(const int *tuples, int length) {
    if (tuples == NULL || length <= 0) return 0;

    int sum = 0;
    for (int i = 0; i < length; i += 2) {
        sum += tuples[i];
    }
    return sum;
}

int main() {
    int data[] = {1, 2, 3, 4, 5, 6};
    int length = sizeof(data) / sizeof(data[0]);
    int result = sumAlternateChains(data, length);
    printf("Sum: %d\n", result);
    return 0;
}