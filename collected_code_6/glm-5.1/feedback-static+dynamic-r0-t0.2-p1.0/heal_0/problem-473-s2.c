#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    int count;
} Tuple;

typedef struct {
    Tuple *items;
    int count;
    int capacity;
} TupleList;

void sort_int_array(int *arr, int count) {
    int i, j, temp;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int tuple_equal(Tuple a, Tuple b) {
    if (a.count != b.count) return 0;
    for (int i = 0; i < a.count; i++) {
        if (a.elements[i] != b.elements[i]) return 0;
    }
    return 1;
}

void tuple_list_init(TupleList *list, int capacity) {
    list->items = (Tuple *)malloc(capacity * sizeof(Tuple));
    if (list->items == NULL) {
        exit(EXIT_FAILURE);
    }
    list->count = 0;
    list->capacity = capacity;
}

void tuple_list_append(TupleList *list, Tuple t) {
    if (list->count == list->capacity) {
        list->capacity *= 2;
        Tuple *new_items = (Tuple *)realloc(list->items, list->capacity * sizeof(Tuple));
        if (new_items == NULL) {
            free(list->items);
            exit(EXIT_FAILURE);
        }
        list->items = new_items;
    }
    list->items[list->count++] = t;
}

void tuple_list_free(TupleList *list) {
    for (int i = 0; i < list->count; i++) {
        free(list->items[i].elements);
    }
    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

TupleList find_tuple_intersection(TupleList list1, TupleList list2) {
    TupleList result;
    tuple_list_init(&result, 10);

    for (int i = 0; i < list1.count; i++) {
        Tuple t1 = list1.items[i];
        int *sorted1 = (int *)malloc(t1.count * sizeof(int));
        if (sorted1 == NULL) {
            tuple_list_free(&result);
            exit(EXIT_FAILURE);
        }
        memcpy(sorted1, t1.elements, t1.count * sizeof(int));
        sort_int_array(sorted1, t1.count);

        for (int j = 0; j < list2.count; j++) {
            Tuple t2 = list2.items[j];
            if (t1.count != t2.count) continue;

            int *sorted2 = (int *)malloc(t2.count * sizeof(int));
            if (sorted2 == NULL) {
                free(sorted1);
                tuple_list_free(&result);
                exit(EXIT_FAILURE);
            }
            memcpy(sorted2, t2.elements, t2.count * sizeof(int));
            sort_int_array(sorted2, t2.count);

            Tuple s1 = {sorted1, t1.count};
            Tuple s2 = {sorted2, t2.count};

            if (tuple_equal(s1, s2)) {
                int found = 0;
                for (int k = 0; k < result.count; k++) {
                    Tuple s_res = result.items[k];
                    if (tuple_equal(s1, s_res)) {
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    Tuple new_tuple;
                    new_tuple.count = t1.count;
                    new_tuple.elements = (int *)malloc(t1.count * sizeof(int));
                    if (new_tuple.elements == NULL) {
                        free(sorted1);
                        free(sorted2);
                        tuple_list_free(&result);
                        exit(EXIT_FAILURE);
                    }
                    memcpy(new_tuple.elements, sorted1, t1.count * sizeof(int));
                    tuple_list_append(&result, new_tuple);
                }
            }
            free(sorted2);
        }
        free(sorted1);
    }

    return result;
}

int main() {
    TupleList list1, list2;
    tuple_list_init(&list1, 4);
    tuple_list_init(&list2, 4);

    int a1[] = {1, 2, 3}; Tuple t1 = {a1, 3};
    int a2[] = {4, 5, 6}; Tuple t2 = {a2, 3};
    int a3[] = {7, 8}; Tuple t3 = {a3, 2};
    int a4[] = {3, 2, 1}; Tuple t4 = {a4, 3};
    int a5[] = {6, 4, 5}; Tuple t5 = {a5, 3};
    int a6[] = {9, 10}; Tuple t6 = {a6, 2};

    tuple_list_append(&list1, t1);
    tuple_list_append(&list1, t2);
    tuple_list_append(&list1, t3);

    tuple_list_append(&list2, t4);
    tuple_list_append(&list2, t5);
    tuple_list_append(&list2, t6);

    TupleList intersection = find_tuple_intersection(list1, list2);

    for (int i = 0; i < intersection.count; i++) {
        printf("(");
        for (int j = 0; j < intersection.items[i].count; j++) {
            printf("%d", intersection.items[i].elements[j]);
            if (j < intersection.items[i].count - 1) printf(", ");
        }
        printf(")\n");
    }

    tuple_list_free(&list1);
    tuple_list_free(&list2);
    tuple_list_free(&intersection);

    return 0;
}