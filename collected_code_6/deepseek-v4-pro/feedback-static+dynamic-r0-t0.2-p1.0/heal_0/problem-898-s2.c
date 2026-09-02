#include <stdio.h>
#include <stdlib.h>

int* extract_continuous_elements(int* list, int list_size, int start_index, int count) {
    if (list == NULL || list_size <= 0 || count <= 0) {
        return NULL;
    }
    
    if (start_index < 0 || start_index >= list_size) {
        return NULL;
    }
    
    if (start_index + count > list_size) {
        return NULL;
    }
    
    int* result = (int*)malloc(count * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < count; i++) {
        result[i] = list[start_index + i];
    }
    
    return result;
}

int main(void) {
    int list[] = {10, 20, 30, 40, 50, 60, 70, 80};
    int list_size = sizeof(list) / sizeof(list[0]);
    int start_index = 2;
    int count = 4;
    
    int* extracted = extract_continuous_elements(list, list_size, start_index, count);
    
    if (extracted != NULL) {
        printf("Extracted elements: ");
        for (int i = 0; i < count; i++) {
            printf("%d ", extracted[i]);
        }
        printf("\n");
        free(extracted);
    } else {
        printf("Failed to extract elements\n");
    }
    
    return 0;
}