#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t len;
} Sublist;

typedef struct {
    Sublist *lists;
    size_t num_lists;
} ListCollection;

size_t count_sublists_with_element(const ListCollection *collection, int element) {
    if (collection == NULL || collection->lists == NULL) {
        return 0;
    }

    size_t count = 0;

    for (size_t i = 0; i < collection->num_lists; i++) {
        if (collection->lists[i].data == NULL) {
            continue;
        }

        int found = 0;
        for (size_t j = 0; j < collection->lists[i].len; j++) {
            if (collection->lists[i].data[j] == element) {
                found = 1;
                break;
            }
        }

        if (found) {
            count++;
        }
    }

    return count;
}

int main(void) {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    int arr3[] = {3, 7, 8};

    Sublist sublists[] = {
        {arr1, sizeof(arr1) / sizeof(arr1[0])},
        {arr2, sizeof(arr2) / sizeof(arr2[0])},
        {arr3, sizeof(arr3) / sizeof(arr3[0])}
    };

    ListCollection collection;
    collection.lists = sublists;
    collection.num_lists = sizeof(sublists) / sizeof(sublists[0]);

    size_t result = count_sublists_with_element(&collection, 3);
    printf("%zu\n", result);

    return EXIT_SUCCESS;
}