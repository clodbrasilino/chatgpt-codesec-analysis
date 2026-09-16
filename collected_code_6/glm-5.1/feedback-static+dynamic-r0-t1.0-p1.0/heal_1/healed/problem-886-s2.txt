#include <stdio.h>
#include <stdlib.h>

double compute_average(const int *list, size_t length) {
    if (list == NULL || length == 0) {
        return 0.0;
    }

    long long sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += list[i];
    }

    return (double)sum / (double)length;
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5};
    size_t length = sizeof(list) / sizeof(list[0]);

    double average = compute_average(list, length);

    printf("%f\n", average);

    return 0;
}