#include <stdio.h>
#include <stdlib.h>

int* extract_continuous(const int* list, size_t list_size, size_t start_index, size_t count, size_t* out_size) {
    if (list == NULL || out_size == NULL) {
        return NULL;
    }

    *out_size = 0;

    if (list_size == 0 || start_index >= list_size) {
        return NULL;
    }

    size_t available = list_size - start_index;
    size_t actual_count = (count < available) ? count : available;

    int* result = (int*)malloc(actual_count * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < actual_count; ++i) {
        result[i] = list[start_index + i];
    }

    *out_size = actual_count;
    return result;
}

int main(void) {
    int data[] = {10, 20, 30, 40, 50, 60, 70};
    size_t data_size = sizeof(data) / sizeof(data[0]);
    size_t out_size = 0;

    int* subset = extract_continuous(data, data_size, 2, 3, &out_size);
    if (subset != NULL) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("%d ", subset[i]);
        }
        printf("\n");
        free(subset);
    }

    subset = extract_continuous(data, data_size, 5, 10, &out_size);
    if (subset != NULL) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("%d ", subset[i]);
        }
        printf("\n");
        free(subset);
    }

    /* Possible weaknesses found:
     *  Assignment 'subset=extract_continuous(NULL,data_size,0,2,&out_size)', assigned value is 0
     *  Calling function 'extract_continuous' returns 0
     */
    subset = extract_continuous(NULL, data_size, 0, 2, &out_size);
    
    /* Possible weaknesses found:
     *  Condition 'subset==NULL' is always true
     *  Condition 'subset==NULL' is always true [knownConditionTrueFalse]
     */
    if (subset == NULL) {
        printf("Extraction failed as expected for NULL input.\n");
    }

    return 0;
}