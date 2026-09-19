#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
} IntList;

typedef struct {
    IntList *lists;
    size_t num_lists;
} NestedList;

int compare_ints(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

int find_common_elements(const NestedList *nested, int **result, size_t *result_size) {
    if (nested == NULL || result == NULL || result_size == NULL) {
        return -1;
    }
    
    *result = NULL;
    *result_size = 0;
    
    if (nested->num_lists == 0 || nested->lists == NULL) {
        return 0;
    }
    
    if (nested->lists[0].size == 0 || nested->lists[0].data == NULL) {
        return 0;
    }
    
    size_t max_size = nested->lists[0].size;
    int *common = malloc(max_size * sizeof(int));
    if (common == NULL) {
        return -1;
    }
    
    memcpy(common, nested->lists[0].data, max_size * sizeof(int));
    size_t common_count = max_size;
    
    qsort(common, common_count, sizeof(int), compare_ints);
    
    for (size_t i = 1; i < nested->num_lists && common_count > 0; i++) {
        if (nested->lists[i].size == 0 || nested->lists[i].data == NULL) {
            common_count = 0;
            break;
        }
        
        int *current = malloc(nested->lists[i].size * sizeof(int));
        if (current == NULL) {
            free(common);
            return -1;
        }
        
        memcpy(current, nested->lists[i].data, nested->lists[i].size * sizeof(int));
        qsort(current, nested->lists[i].size, sizeof(int), compare_ints);
        
        size_t write_idx = 0;
        size_t j = 0;
        size_t k = 0;
        
        while (j < common_count && k < nested->lists[i].size) {
            if (common[j] < current[k]) {
                j++;
            } else if (common[j] > current[k]) {
                k++;
            } else {
                if (write_idx == 0 || common[write_idx - 1] != common[j]) {
                    common[write_idx++] = common[j];
                }
                j++;
                k++;
            }
        }
        
        common_count = write_idx;
        free(current);
    }
    
    if (common_count == 0) {
        free(common);
        return 0;
    }
    
    int *final_result = realloc(common, common_count * sizeof(int));
    if (final_result == NULL) {
        free(common);
        return -1;
    }
    
    *result = final_result;
    *result_size = common_count;
    return 0;
}

void free_nested_list(NestedList *nested) {
    if (nested == NULL) {
        return;
    }
    
    if (nested->lists != NULL) {
        for (size_t i = 0; i < nested->num_lists; i++) {
            free(nested->lists[i].data);
        }
        free(nested->lists);
        nested->lists = NULL;
    }
    nested->num_lists = 0;
}

int main(void) {
    NestedList nested = {NULL, 0};
    int *result = NULL;
    size_t result_size = 0;
    int status = 0;
    
    nested.num_lists = 4;
    nested.lists = calloc(nested.num_lists, sizeof(IntList));
    if (nested.lists == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    int data0[] = {1, 2, 3, 4, 5};
    int data1[] = {2, 4, 5, 8, 10};
    int data2[] = {2, 3, 4, 5, 6};
    int data3[] = {1, 2, 4, 5, 7};
    
    const size_t sizes[] = {5, 5, 5, 5};
    const int *data_arrays[] = {data0, data1, data2, data3};
    
    for (size_t i = 0; i < nested.num_lists; i++) {
        nested.lists[i].size = sizes[i];
        nested.lists[i].data = malloc(sizes[i] * sizeof(int));
        if (nested.lists[i].data == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_nested_list(&nested);
            return EXIT_FAILURE;
        }
        memcpy(nested.lists[i].data, data_arrays[i], sizes[i] * sizeof(int));
    }
    
    status = find_common_elements(&nested, &result, &result_size);
    if (status != 0) {
        fprintf(stderr, "Error finding common elements\n");
        free_nested_list(&nested);
        return EXIT_FAILURE;
    }
    
    printf("Common elements: ");
    for (size_t i = 0; i < result_size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    free(result);
    free_nested_list(&nested);
    
    return EXIT_SUCCESS;
}