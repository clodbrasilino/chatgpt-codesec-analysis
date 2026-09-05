#include <stdio.h>
#include <stdlib.h>

int sum_three_lowest_positive(const int *array, size_t size) {
    int m1 = -1, m2 = -1, m3 = -1;

    if (array == NULL || size == 0) {
        return 0;
    }

    for (size_t i = 0; i < size; i++) {
        if (array[i] > 0) {
            if (m1 == -1 || array[i] < m1) {
                m3 = m2;
                m2 = m1;
                m1 = array[i];
            } else if (m2 == -1 || array[i] < m2) {
                m3 = m2;
                m2 = array[i];
            } else if (m3 == -1 || array[i] < m3) {
                m3 = array[i];
            }
        }
    }

    if (m3 == -1) {
        return 0;
    }

    return m1 + m2 + m3;
}

int main(void) {
    int data[] = {4, 5, -2, 1, 8, -9, 2};
    size_t size = sizeof(data) / sizeof(data[0]);

    int result = sum_three_lowest_positive(data, size);

    printf("%d\n", result);

    return 0;
}