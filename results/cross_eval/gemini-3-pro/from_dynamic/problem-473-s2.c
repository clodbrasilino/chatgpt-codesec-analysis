#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

bool contains(const int *array, int size, int element) {
    for (int i = 0; i < size; ++i) {
        if (array[i] == element) {
            return true;
        }
    }
    return false;
}

Tuple tuple_intersection(const TupleList *list) {
    Tuple result = {NULL, 0};

    if (list == NULL || list->count == 0 || list->tuples == NULL) {
        return result;
    }

    int min_size = list->tuples[0].size;
    int min_index = 0;
    for (int i = 1; i < list->count; ++i) {
        if (list->tuples[i].size < min_size) {
            min_size = list->tuples[i].size;
            min_index = i;
        }
    }

    int *temp = (int *)malloc(min_size * sizeof(int));
    if (temp == NULL) {
        return result;
    }

    int temp_count = 0;

    for (int i = 0; i < list->tuples[min_index].size; ++i) {
        int elem = list->tuples[min_index].elements[i];
        if (!contains(temp, temp_count, elem)) {
            bool in_all = true;
            for (int j = 0; j < list->count; ++j) {
                if (j != min_index) {
                    if (!contains(list->tuples[j].elements, list->tuples[j].size, elem)) {
                        in_all = false;
                        break;
                    }
                }
            }
            if (in_all) {
                temp[temp_count++] = elem;
            }
        }
    }

    if (temp_count > 0) {
        result.elements = (int *)malloc(temp_count * sizeof(int));
        if (result.elements != NULL) {
            for (int i = 0; i < temp_count; ++i) {
                result.elements[i] = temp[i];
            }
            result.size = temp_count;
        }
    }

    free(temp);
    return result;
}

int main(void) {
    int t1_data[] = {1, 2, 3, 4, 5};
    int t2_data[] = {4, 5, 6, 7, 1};
    int t3_data[] = {1, 5, 8, 9};

    Tuple tuples[3];
    tuples[0].elements = t1_data;
    tuples[0].size = 5;
    tuples[1].elements = t2_data;
    tuples[1].size = 5;
    tuples[2].elements = t3_data;
    tuples[2].size = 4;

    TupleList list = {tuples, 3};

    Tuple intersection = tuple_intersection(&list);

    if (intersection.elements != NULL) {
        for (int i = 0; i < intersection.size; ++i) {
            printf("%d ", intersection.elements[i]);
        }
        printf("\n");
        free(intersection.elements);
    } else {
        printf("\n");
    }

    return 0;
}