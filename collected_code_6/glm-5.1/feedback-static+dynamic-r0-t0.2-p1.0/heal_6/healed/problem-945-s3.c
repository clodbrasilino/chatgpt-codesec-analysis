#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t size;
} Set;

Set tuples_to_set(const int *tuples, size_t tuple_count, size_t tuple_size) {
    Set empty_set = {NULL, 0};
    size_t total_elements = tuple_count * tuple_size;
    if (total_elements == 0) {
        Set result = {NULL, 0};
        return result;
    }
    
    int *temp = (int *)malloc(total_elements * sizeof(int));
    if (temp == NULL) {
        return empty_set;
    }
    
    size_t unique_count = 0;
    
    for (size_t i = 0; i < total_elements; i++) {
        int found = 0;
        for (size_t j = 0; j < unique_count; j++) {
            if (temp[j] == tuples[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            temp[unique_count++] = tuples[i];
        }
    }
    
    int *set_elements = (int *)malloc(unique_count * sizeof(int));
    if (set_elements == NULL) {
        free(temp);
        return empty_set;
    }
    
    if (unique_count > 0) {
        size_t copy_size = unique_count * sizeof(int);
        size_t dest_size = unique_count * sizeof(int);
        if (copy_size <= dest_size) {
            memcpy(set_elements, temp, copy_size);
        }
    }
    free(temp);
    
    Set result;
    result.elements = set_elements;
    result.size = unique_count;
    
    return result;
}

void free_set(Set *set) {
    if (set != NULL) {
        free(set->elements);
        set->elements = NULL;
        set->size = 0;
    }
}

int main(void) {
    int data[][3] = {
        {1, 2, 3},
        {2, 3, 4},
        {4, 5, 1}
    };
    
    size_t tuple_count = sizeof(data) / sizeof(data[0]);
    size_t tuple_size = sizeof(data[0]) / sizeof(data[0][0]);
    
    Set my_set = tuples_to_set((const int *)data, tuple_count, tuple_size);
    
    if (my_set.elements != NULL) {
        for (size_t i = 0; i < my_set.size; i++) {
            printf("%d ", my_set.elements[i]);
        }
        printf("\n");
    }
    
    free_set(&my_set);
    
    return 0;
}