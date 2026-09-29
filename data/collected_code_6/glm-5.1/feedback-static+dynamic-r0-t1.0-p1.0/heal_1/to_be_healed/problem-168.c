#include <stdio.h>
#include <stdlib.h>

size_t find_frequency(const int *array, size_t size, int target) {
    size_t count = 0;
    if (array == NULL) {
        return 0;
    }
    for (size_t i = 0; i < size; i++) {
        if (array[i] == target) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int data[] = {1, 2, 3, 2, 4, 2, 5};
    size_t data_size = sizeof(data) / sizeof(data[0]);
    int target = 2;
    
    size_t frequency = find_frequency(data, data_size, target);
    
    /* Possible weaknesses found:
     *  %d in format string (no. 1) requires 'int' but the argument type is 'size_t {aka unsigned long}'. [invalidPrintfArgType_sint]
     */
    printf("%d\n", frequency);
    
    return EXIT_SUCCESS;
}