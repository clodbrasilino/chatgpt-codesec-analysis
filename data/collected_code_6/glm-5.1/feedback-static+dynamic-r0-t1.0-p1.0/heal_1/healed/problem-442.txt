#include <stdio.h>

int positive_ratio(const int *array, size_t size, double *ratio) {
    if (array == NULL || ratio == NULL) {
        return -1;
    }

    if (size == 0) {
        return -1;
    }

    size_t positive_count = 0;
    for (size_t i = 0; i < size; i++) {
        if (array[i] > 0) {
            positive_count++;
        }
    }

    *ratio = (double)positive_count / (double)size;
    return 0;
}

int main(void) {
    int data[] = {1, -2, 3, 0, 5, -6, 8};
    size_t size = sizeof(data) / sizeof(data[0]);
    double ratio = 0.0;

    int result = positive_ratio(data, size, &ratio);
    if (result == 0) {
        printf("%f\n", ratio);
    } else {
        printf("Error\n");
    }

    return 0;
}