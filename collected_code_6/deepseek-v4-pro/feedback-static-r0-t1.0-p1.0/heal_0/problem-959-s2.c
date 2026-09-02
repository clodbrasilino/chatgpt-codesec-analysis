#include <stdio.h>
#include <stdlib.h>

double list_average(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return 0.0;
    }
    
    long long sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += list[i];
    }
    
    return (double)sum / (double)size;
}

int main(void) {
    int test_array[] = {10, 20, 30, 40, 50};
    size_t test_size = sizeof(test_array) / sizeof(test_array[0]);
    
    double avg = list_average(test_array, test_size);
    printf("Average: %.2f\n", avg);
    
    double empty_avg = list_average(NULL, 0);
    printf("Empty list average: %.2f\n", empty_avg);
    
    return 0;
}