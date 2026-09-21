#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t length;
} IntList;

typedef struct {
    IntList *lists;
    size_t count;
} ListOfLists;

static void free_list_of_lists(ListOfLists *lol)
{
    if (lol == NULL) {
        return;
    }

    if (lol->lists != NULL) {
        for (size_t i = 0; i < lol->count; i++) {
            free(lol->lists[i].data);
            lol->lists[i].data = NULL;
        }
        free(lol->lists);
        lol->lists = NULL;
    }
    lol->count = 0;
}

static ListOfLists find_max_length_lists(const IntList *lists, size_t count)
{
    ListOfLists result;
    size_t max_length = 0;
    size_t max_count = 0;

    result.lists = NULL;
    result.count = 0;

    if (lists == NULL || count == 0) {
        return result;
    }

    for (size_t i = 0; i < count; i++) {
        if (lists[i].length > 0 && lists[i].data == NULL) {
            return result;
        }
        if (lists[i].length > max_length) {
            max_length = lists[i].length;
        }
    }

    for (size_t i = 0; i < count; i++) {
        if (lists[i].length == max_length) {
            max_count++;
        }
    }

    if (max_length > SIZE_MAX / sizeof(int)) {
        return result;
    }

    size_t copy_size = max_length * sizeof(int);

    result.lists = (IntList *)calloc(max_count, sizeof(IntList));
    if (result.lists == NULL) {
        return result;
    }

    size_t j = 0;
    for (size_t i = 0; i < count; i++) {
        if (lists[i].length == max_length) {
            if (max_length > 0) {
                if (lists[i].length > SIZE_MAX / sizeof(int) ||
                    lists[i].length * sizeof(int) > copy_size) {
                    result.count = j;
                    free_list_of_lists(&result);
                    return result;
                }
                result.lists[j].data = (int *)malloc(copy_size);
                if (result.lists[j].data == NULL) {
                    result.count = j;
                    free_list_of_lists(&result);
                    return result;
                }
                memcpy(result.lists[j].data, lists[i].data, copy_size);
            } else {
                result.lists[j].data = NULL;
            }
            result.lists[j].length = max_length;
            j++;
        }
    }

    result.count = j;
    return result;
}

int main(void)
{
    int a[] = {1, 2, 3};
    int b[] = {4, 5};
    int c[] = {6, 7, 8, 9};
    int d[] = {10, 11, 12, 13};
    int e[] = {14};

    IntList lists[] = {
        {a, 3},
        {b, 2},
        {c, 4},
        {d, 4},
        {e, 1}
    };

    size_t count = sizeof(lists) / sizeof(lists[0]);

    ListOfLists max_lists = find_max_length_lists(lists, count);

    if (max_lists.count == 0) {
        printf("No lists found.\n");
    } else {
        printf("Maximum length: %zu\n", max_lists.lists[0].length);
        printf("Number of lists with maximum length: %zu\n", max_lists.count);
        for (size_t i = 0; i < max_lists.count; i++) {
            printf("List %zu: ", i + 1);
            for (size_t k = 0; k < max_lists.lists[i].length; k++) {
                printf("%d ", max_lists.lists[i].data[k]);
            }
            printf("\n");
        }
    }

    free_list_of_lists(&max_lists);

    return 0;
}