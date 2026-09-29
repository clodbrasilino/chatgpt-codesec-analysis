#include <stdio.h>
#include <stdlib.h>

int* remove_two_duplicates(int* const lists[], const int list_sizes[], int num_lists, int result_size, int* result_len) {
    int* result = (int*)malloc(result_size * sizeof(int));
    if (result == NULL) {
        *result_len = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < num_lists; i++) {
        int* const current_list = lists[i];
        int current_size = list_sizes[i];
        for (int j = 0; j < current_size; j++) {
            int val = current_list[j];
            int is_dup = 0;
            for (int k = 0; k < count; k++) {
                if (result[k] == val) {
                    is_dup = 1;
                    break;
                }
            }
            if (!is_dup) {
                if (count < result_size) {
                    result[count++] = val;
                }
            }
        }
    }

    *result_len = count;
    return result;
}

int main() {
    int list1[] = {1, 2, 3, 4};
    int list2[] = {3, 4, 5, 6};
    int list3[] = {5, 6, 7, 8};
    
    int* const lists[] = {list1, list2, list3};
    const int list_sizes[] = {4, 4, 4};
    int num_lists = 3;
    int result_size = 8;
    int result_len = 0;

    int* result = remove_two_duplicates(lists, list_sizes, num_lists, result_size, &result_len);

    if (result != NULL) {
        for (int i = 0; i < result_len; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}