#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list_sizes' can be declared as pointer to const [constParameterPointer]
 */
int* remove_two_duplicates(int** lists, int* list_sizes, int num_lists, int* result_size) {
    int total_capacity = 0;
    for (int i = 0; i < num_lists; i++) {
        total_capacity += list_sizes[i];
    }

    if (total_capacity == 0) {
        *result_size = 0;
        return NULL;
    }

    int* all_elements = (int*)malloc(total_capacity * sizeof(int));
    if (all_elements == NULL) {
        *result_size = 0;
        return NULL;
    }

    int total_count = 0;
    for (int i = 0; i < num_lists; i++) {
        if (lists[i] != NULL && list_sizes[i] > 0) {
            for (int j = 0; j < list_sizes[i]; j++) {
                all_elements[total_count++] = lists[i][j];
            }
        }
    }

    if (total_count == 0) {
        free(all_elements);
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < total_count - 1; i++) {
        for (int j = 0; j < total_count - i - 1; j++) {
            if (all_elements[j] > all_elements[j + 1]) {
                int temp = all_elements[j];
                all_elements[j] = all_elements[j + 1];
                all_elements[j + 1] = temp;
            }
        }
    }

    int* result = (int*)malloc(total_count * sizeof(int));
    if (result == NULL) {
        free(all_elements);
        *result_size = 0;
        return NULL;
    }

    int res_idx = 0;
    int i = 0;
    while (i < total_count) {
        if (i + 1 < total_count && all_elements[i] == all_elements[i + 1]) {
            result[res_idx++] = all_elements[i];
            i += 2;
        } else {
            i++;
        }
    }

    free(all_elements);

    if (res_idx == 0) {
        free(result);
        *result_size = 0;
        return NULL;
    }

    int* final_result = (int*)realloc(result, res_idx * sizeof(int));
    if (final_result == NULL) {
        *result_size = res_idx;
        return result;
    }

    *result_size = res_idx;
    return final_result;
}

int main() {
    int list1[] = {1, 2, 3, 4};
    int list2[] = {3, 4, 5, 6};
    int list3[] = {5, 6, 7, 8};
    
    int* lists[] = {list1, list2, list3};
    int list_sizes[] = {4, 4, 4};
    int num_lists = 3;
    int result_size = 0;

    int* result = remove_two_duplicates(lists, list_sizes, num_lists, &result_size);

    for (int i = 0; i < result_size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    if (result != NULL) {
        free(result);
    }

    return 0;
}