#include <stdio.h>
#include <stdlib.h>

int* remove_two_duplicates(int* lists[], int list_sizes[], int num_lists, int result_size, int* out_size) {
    int* result = (int*)malloc(result_size * sizeof(int));
    if (result == NULL) {
        *out_size = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < num_lists; i++) {
        int* current_list = lists[i];
        int current_size = list_sizes[i];
        for (int j = 0; j < current_size; j++) {
            int val = current_list[j];
            int occurrences = 0;
            for (int k = 0; k < current_size; k++) {
                if (current_list[k] == val) {
                    occurrences++;
                }
            }
            if (occurrences == 2) {
                int already_exists = 0;
                for (int m = 0; m < count; m++) {
                    if (result[m] == val) {
                        already_exists = 1;
                        break;
                    }
                }
                if (!already_exists) {
                    if (count < result_size) {
                        result[count++] = val;
                    }
                }
            }
        }
    }

    *out_size = count;
    return result;
}

int main() {
    int list1[] = {1, 2, 2, 3, 4};
    int list2[] = {5, 5, 6, 7, 8};
    int list3[] = {9, 10, 11, 12, 12};
    
    int* lists[] = {list1, list2, list3};
    int list_sizes[] = {5, 5, 5};
    int num_lists = 3;
    int result_size = 10;
    int out_size = 0;

    int* result = remove_two_duplicates(lists, list_sizes, num_lists, result_size, &out_size);

    if (result != NULL) {
        for (int i = 0; i < out_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}