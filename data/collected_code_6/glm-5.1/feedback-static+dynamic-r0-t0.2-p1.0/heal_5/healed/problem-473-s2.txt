#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t count;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
    size_t capacity;
} TupleList;

void sort_int_array(int *arr, size_t count) {
    for (size_t i = 0; i < count - 1; i++) {
        for (size_t j = 0; j < count - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int tuple_equal(Tuple a, Tuple b) {
    if (a.count != b.count) return 0;
    for (size_t i = 0; i < a.count; i++) {
        if (a.elements[i] != b.elements[i]) return 0;
    }
    return 1;
}

void tuple_list_init(TupleList *list, size_t capacity) {
    if (capacity == 0) capacity = 1;
    list->items = (Tuple *)malloc(capacity * sizeof(Tuple));
    if (list->items == NULL) {
        exit(EXIT_FAILURE);
    }
    list->count = 0;
    list->capacity = capacity;
}

void tuple_list_append(TupleList *list, Tuple t) {
    if (list->count == list->capacity) {
        size_t new_capacity = list->capacity * 2;
        Tuple *new_items = (Tuple *)realloc(list->items, new_capacity * sizeof(Tuple));
        if (new_items == NULL) {
            free(list->items);
            exit(EXIT_FAILURE);
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    list->items[list->count++] = t;
}

void tuple_list_free(TupleList *list) {
    for (size_t i = 0; i < list->count; i++) {
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

    for (size_t i = 0; i < list1.count; i++) {
        Tuple t1 = list1.items[i];
        if (t1.count > 0) {
            int *sorted1 = (int *)malloc(t1.count * sizeof(int));
            if (sorted1 == NULL) {
                tuple_list_free(&result);
                exit(EXIT_FAILURE);
            }
            memcpy(sorted1, t1.elements, t1.count * sizeof(int));
            sort_int_array(sorted1, t1.count);

            for (size_t j = 0; j < list2.count; j++) {
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
                    for (size_t k = 0; k < result.count; k++) {
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
        } else {
            for (size_t j = 0; j < list2.count; j++) {
                Tuple t2 = list2.items[j];
                if (t2.count != 0) continue;
                
                int found = 0;
                for (size_t k = 0; k < result.count; k++) {
                    if (result.items[k].count == 0) {
                        found = 1;
                        break;
                    }
                }
                
                if (!found) {
                    Tuple new_tuple;
                    new_tuple.count = 0;
                    new_tuple.elements = NULL;
                    tuple_list_append(&result, new_tuple);
                }
            }
        }
    }

    return result;
}

void append_tuple_safe(TupleList *list, const int *arr, size_t count) {
    Tuple t;
    t.count = count;
    if (count > 0) {
        t.elements = (int *)malloc(count * sizeof(int));
        if (t.elements == NULL) {
            exit(EXIT_FAILURE);
        }
        memcpy(t.elements, arr, count * sizeof(int));
    } else {
        t.elements = NULL;
    }
    tuple_list_append(list, t);
}

int main() {
    TupleList list1, list2;
    tuple_list_init(&list1, 4);
    tuple_list_init(&list2, 4);

    int a1[] = {1, 2, 3};
    int a2[] = {4, 5, 6};
    int a3[] = {7, 8};
    int a4[] = {3, 2, 1};
    int a5[] = {6, 4, 5};
    int a6[] = {9, 10};

    append_tuple_safe(&list1, a1, sizeof(a1) / sizeof(a1[0]));
    append_tuple_safe(&list1, a2, sizeof(a2) / sizeof(a2[0]));
    append_tuple_safe(&list1, a3, sizeof(a3) / sizeof(a3[0]));

    append_tuple_safe(&list2, a4, sizeof(a4) / sizeof(a4[0]));
    append_tuple_safe(&list2, a5, sizeof(a5) / sizeof(a5[0]));
    append_tuple_safe(&list2, a6, sizeof(a6) / sizeof(a6[0]));

    TupleList intersection = find_tuple_intersection(list1, list2);

    for (size_t i = 0; i < intersection.count; i++) {
        printf("(");
        for (size_t j = 0; j < intersection.items[i].count; j++) {
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