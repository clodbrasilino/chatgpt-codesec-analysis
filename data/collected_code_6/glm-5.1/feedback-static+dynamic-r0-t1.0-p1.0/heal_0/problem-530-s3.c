#include <stdio.h>

double find_negative_ratio(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0.0;
    }

    size_t negative_count = 0;

    for (size_t i = 0; i < size; ++i) {
        if (array[i] < 0) {
            negative_count++;
        }
    }

    return (double)negative_count / (double)size;
}

int main(void) {
    int array[] = {1, -2, 3, -4, -5, 6};
    size_t size = sizeof(array) / sizeof(array[0]);
    
    double ratio = find_negative_ratio(array, size);
    
    printf("%f\n", ratio);
    
    return 0;
}