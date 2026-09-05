#include <stdio.h>
#include <stdlib.h>

int* find_max_sum_list(int** lists, const int* lengths, int num_lists, int* result_length) {
    if (lists == NULL || lengths == NULL || num_lists <= 0) {
        *result_length = 0;
        return NULL;
    }

    long long max_sum = -1;
    int max_index = -1;

    for (int i = 0; i < num_lists; i++) {
        if (lists[i] == NULL || lengths[i] <= 0) {
            continue;
        }

        long long current_sum = 0;
        for (int j = 0; j < lengths[i]; j++) {
            current_sum += lists[i][j];
        }

        if (max_index == -1 || current_sum > max_sum) {
            max_sum = current_sum;
            max_index = i;
        }
    }

    if (max_index == -1) {
        *result_length = 0;
        return NULL;
    }

    *result_length = lengths[max_index];
    return lists[max_index];
}

int main() {
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5};
    int list3[] = {10};
    int list4[] = {-1, -2, -3};

    int num_lists = 4;
    int* lists[] = {list1, list2, list3, list4};
    const int lengths[] = {3, 2, 1, 3};

    int result_length = 0;
    const int* result = find_max_sum_list(lists, lengths, num_lists, &result_length);

    if (result != NULL && result_length > 0) {
        for (int i = 0; i < result_length; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    } else {
        printf("No valid list found.\n");
    }

    return 0;
}