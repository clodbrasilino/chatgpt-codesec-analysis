#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
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
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int list_size = sizeof(list) / sizeof(list[0]);
    
    int* extracted = extract_continuous_elements(list, list_size, 2, 4);
    
    if (extracted != NULL) {
        printf("Extracted elements: ");
        for (int i = 0; i < 4; i++) {
            printf("%d ", extracted[i]);
        }
        printf("\n");
        free(extracted);
    } else {
        printf("Failed to extract elements\n");
    }
    
    /* Possible weaknesses found:
     *  Variable 'invalid_extract' can be declared as pointer to const [constVariablePointer]
     */
    int* invalid_extract = extract_continuous_elements(list, list_size, 8, 5);
    if (invalid_extract == NULL) {
        printf("Invalid extraction correctly rejected\n");
    }
    
    return 0;
}