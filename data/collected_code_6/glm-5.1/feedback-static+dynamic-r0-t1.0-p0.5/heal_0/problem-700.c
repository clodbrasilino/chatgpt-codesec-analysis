#include <stdio.h>
#include <stdlib.h>

size_t count_in_range(const int *list, size_t size, int lower, int upper) {
    size_t count = 0;
    if (list == NULL) {
        return 0;
    }
    for (size_t i = 0; i < size; i++) {
        if (list[i] >= lower && list[i] <= upper) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int data[] = {1, 5, 12, 15, 20, 25, 30};
    size_t data_size = sizeof(data) / sizeof(data[0]);
    int lower = 10;
    int upper = 25;
    
    size_t result = count_in_range(data, data_size, lower, upper);
    
    printf("%zu\n", result);
    return 0;
}