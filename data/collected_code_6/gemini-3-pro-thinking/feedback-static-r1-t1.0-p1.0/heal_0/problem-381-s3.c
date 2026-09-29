#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SUCCESS = 0,
    ERR_NULL_POINTER = 1,
    ERR_OUT_OF_BOUNDS = 2,
    ERR_MEM_ALLOC = 3
} Status;

typedef struct {
    int *data;
    size_t size;
} InnerList;

static int compare_lists(const InnerList *a, const InnerList *b, size_t index) {
    if (a->data[index] < b->data[index]) {
        return -1;
    }
    if (a->data[index] > b->data[index]) {
        return 1;
    }
    return 0;
}

static void merge(InnerList **arr, InnerList **temp, size_t left, size_t mid, size_t right, size_t index) {
    size_t i = left;
    size_t j = mid + 1;
    size_t k = left;

    while (i <= mid && j <= right) {
        if (compare_lists(arr[i], arr[j], index) <= 0) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

static void merge_sort(InnerList **arr, InnerList **temp, size_t left, size_t right, size_t index) {
    if (left >= right) {
        return;
    }
    size_t mid = left + (right - left) / 2;
    merge_sort(arr, temp, left, mid, index);
    merge_sort(arr, temp, mid + 1, right, index);
    merge(arr, temp, left, mid, right, index);
}

Status sort_list_of_lists(InnerList **lists, size_t count, size_t sort_index) {
    if (!lists) {
        return ERR_NULL_POINTER;
    }
    if (count <= 1) {
        return SUCCESS;
    }

    for (size_t i = 0; i < count; i++) {
        if (!lists[i] || !lists[i]->data || sort_index >= lists[i]->size) {
            return ERR_OUT_OF_BOUNDS;
        }
    }

    InnerList **temp = (InnerList **)malloc(count * sizeof(InnerList *));
    if (!temp) {
        return ERR_MEM_ALLOC;
    }

    merge_sort(lists, temp, 0, count - 1, sort_index);

    free(temp);
    return SUCCESS;
}

static void free_list_of_lists(InnerList **lists, size_t count) {
    if (!lists) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        if (lists[i]) {
            if (lists[i]->data) {
                free(lists[i]->data);
            }
            free(lists[i]);
        }
    }
    free(lists);
}

int main(void) {
    size_t row_count = 3;
    size_t col_count = 3;

    InnerList **lists = (InnerList **)malloc(row_count * sizeof(InnerList *));
    if (!lists) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < row_count; i++) {
        lists[i] = NULL;
    }

    for (size_t i = 0; i < row_count; i++) {
        lists[i] = (InnerList *)malloc(sizeof(InnerList));
        if (!lists[i]) {
            free_list_of_lists(lists, row_count);
            return EXIT_FAILURE;
        }
        
        lists[i]->data = NULL;
        lists[i]->size = 0;

        lists[i]->data = (int *)malloc(col_count * sizeof(int));
        if (!lists[i]->data) {
            free_list_of_lists(lists, row_count);
            return EXIT_FAILURE;
        }
        lists[i]->size = col_count;
    }

    lists[0]->data[0] = 3; lists[0]->data[1] = 10; lists[0]->data[2] = 5;
    lists[1]->data[0] = 1; lists[1]->data[1] = 20; lists[1]->data[2] = 2;
    lists[2]->data[0] = 2; lists[2]->data[1] = 5;  lists[2]->data[2] = 8;

    Status status = sort_list_of_lists(lists, row_count, 1);

    if (status == SUCCESS) {
        for (size_t i = 0; i < row_count; i++) {
            for (size_t j = 0; j < lists[i]->size; j++) {
                printf("%d ", lists[i]->data[j]);
            }
            printf("\n");
        }
    } else {
        printf("Error sorting lists. Error code: %d\n", status);
    }

    free_list_of_lists(lists, row_count);

    return (status == SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE;
}