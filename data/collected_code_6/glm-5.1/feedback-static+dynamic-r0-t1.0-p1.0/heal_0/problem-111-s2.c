#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} List;

typedef struct {
    List *lists;
    int num_lists;
} NestedList;

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int remove_duplicates(int *arr, int size) {
    if (size <= 1) return size;
    int j = 0;
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] != arr[i + 1]) {
            arr[j++] = arr[i];
        }
    }
    arr[j++] = arr[size - 1];
    return j;
}

int find_common(NestedList nested, int **result, int *result_size) {
    if (nested.num_lists == 0 || nested.lists == NULL) {
        *result = NULL;
        *result_size = 0;
        return 0;
    }

    for (int i = 0; i < nested.num_lists; i++) {
        if (nested.lists[i].size > 0 && nested.lists[i].elements != NULL) {
            qsort(nested.lists[i].elements, nested.lists[i].size, sizeof(int), cmp);
            nested.lists[i].size = remove_duplicates(nested.lists[i].elements, nested.lists[i].size);
        }
    }

    int capacity = nested.lists[0].size;
    int *common = (int *)malloc(capacity * sizeof(int));
    if (common == NULL) {
        return -1;
    }
    int common_size = 0;

    for (int i = 0; i < nested.lists[0].size; i++) {
        int candidate = nested.lists[0].elements[i];
        int is_common = 1;

        for (int j = 1; j < nested.num_lists; j++) {
            int found = 0;
            if (nested.lists[j].size > 0 && nested.lists[j].elements != NULL) {
                int *item = (int *)bsearch(&candidate, nested.lists[j].elements, nested.lists[j].size, sizeof(int), cmp);
                if (item != NULL) {
                    found = 1;
                }
            }
            if (!found) {
                is_common = 0;
                break;
            }
        }

        if (is_common) {
            if (common_size >= capacity) {
                capacity *= 2;
                int *temp = (int *)realloc(common, capacity * sizeof(int));
                if (temp == NULL) {
                    free(common);
                    return -1;
                }
                common = temp;
            }
            common[common_size++] = candidate;
        }
    }

    *result = common;
    *result_size = common_size;
    return 0;
}

int main() {
    int arr0[] = {1, 5, 2, 1, 3, 4};
    int arr1[] = {2, 5, 7, 6, 2};
    int arr2[] = {5, 2, 9, 10, 5};

    List lists_data[3] = {
        {arr0, 6},
        {arr1, 5},
        {arr2, 5}
    };

    NestedList nested = {lists_data, 3};

    int *common_elements = NULL;
    int common_count = 0;

    int status = find_common(nested, &common_elements, &common_count);

    if (status == 0) {
        printf("Common elements: ");
        for (int i = 0; i < common_count; i++) {
            printf("%d ", common_elements[i]);
        }
        printf("\n");
        free(common_elements);
    } else {
        printf("Memory allocation failed\n");
    }

    return 0;
}