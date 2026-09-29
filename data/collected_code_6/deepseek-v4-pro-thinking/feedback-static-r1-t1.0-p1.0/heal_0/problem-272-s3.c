#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

typedef struct {
    Tuple *records;
    size_t count;
} TupleList;

int extract_rear_elements(const TupleList *list, int *rear_elements, size_t rear_capacity, size_t *rear_count)
{
    size_t i;

    if (list == NULL || rear_count == NULL) {
        return -1;
    }

    *rear_count = 0;

    if (list->count == 0) {
        return 0;
    }

    if (list->records == NULL || rear_elements == NULL || rear_capacity < list->count) {
        return -1;
    }

    for (i = 0; i < list->count; ++i) {
        if (list->records[i].elements == NULL || list->records[i].length == 0) {
            return -1;
        }
        rear_elements[i] = list->records[i].elements[list->records[i].length - 1];
    }

    *rear_count = list->count;
    return 0;
}

int main(void)
{
    int first[] = {10, 20, 30};
    int second[] = {40, 50};
    int third[] = {60};

    Tuple records[] = {
        {first, 3},
        {second, 2},
        {third, 1}
    };
    TupleList list = {records, 3};

    int *rear;
    size_t rear_count = 0;
    size_t i;

    if (list.count > (size_t)-1 / sizeof(int)) {
        return EXIT_FAILURE;
    }

    rear = malloc(list.count * sizeof(int));
    if (rear == NULL) {
        return EXIT_FAILURE;
    }

    if (extract_rear_elements(&list, rear, list.count, &rear_count) != 0) {
        free(rear);
        return EXIT_FAILURE;
    }

    for (i = 0; i < rear_count; ++i) {
        printf("%d\n", rear[i]);
    }

    free(rear);
    return EXIT_SUCCESS;
}