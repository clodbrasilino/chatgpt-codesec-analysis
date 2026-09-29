#include <stdio.h>
#include <stdlib.h>

int* find_greater_than(const int* list, int size, int threshold, int* result_size) {
    if (result_size == NULL) {
        return NULL;
    }
    
    *result_size = 0;
    
    if (list == NULL || size <= 0) {
        return NULL;
    }
    
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] > threshold) {
            count++;
        }
    }
    
    if (count == 0) {
        return NULL;
    }
    
    int* result = (int*)malloc(count * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    
    int index = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] > threshold) {
            result[index++] = list[i];
        }
    }
    
    *result_size = count;
    return result;
}

int main(void) {
    int list[] = {10, 25, 30, 15, 40, 50, 5};
    int size = sizeof(list) / sizeof(list[0]);
    int threshold = 20;
    int result_size = 0;
    
    int* result = find_greater_than(list, size, threshold, &result_size);
    
    if (result == NULL) {
        printf("No values greater than %d found\n", threshold);
        return 0;
    }
    
    printf("Values greater than %d: ", threshold);
    for (int i = 0; i < result_size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    free(result);
    
    return 0;
}