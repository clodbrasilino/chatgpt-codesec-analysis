#include <stdio.h>
#include <stdlib.h>

double average(int *list, int length) {
    if (length <= 0) return 0;
    double sum = 0;
    for (int i = 0; i < length; ++i) {
        sum += list[i];
    }
    return sum / length;
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    int length = sizeof(list) / sizeof(list[0]);
    printf("Average: %.2f\n", average(list, length));
    return 0;
}