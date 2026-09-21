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
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int tuple_equal(Tuple a, Tuple b) {
    if (a.count != b.count) {
        return 0;
    }
    for (int i = 0; i < a.count; i++) {
        if (a.elements[i] != b.elements[i]) {
            return 0;
        }
    }
    return 1;
}

TupleList find_tuple_intersection(TupleList list1, TupleList list2) {
    TupleList result;
    result.count = 0;
    result.capacity = 16;
    result.items = (Tuple *)malloc(result.capacity * sizeof(Tuple));
    if (result.items == NULL) {
        result.capacity = 0;
        return result;
    }

    for (int i = 0; i < list1.count; i++) {
        Tuple t1 = list1.items[i];
        int *sorted1 = (int *)malloc(t1.count * sizeof(int));
        if (sorted1 == NULL) {
            for (int k = 0; k < result.count; k++) {
                free(result.items[k].elements);
            }
            free(result.items);
            result.items = NULL;
            result.count = 0;
            result.capacity = 0;
            return result;
        }
        memcpy(sorted1, t1.elements, t1.count * sizeof(int));
        sort_int_array(sorted1, t1.count);

        for (int j = 0; j < list2.count; j++) {
            Tuple t2 = list2.items[j];
            if (t1.count != t2.count) {
                continue;
            }

            int *sorted2 = (int *)malloc(t2.count * sizeof(int));
            if (sorted2 == NULL) {
                free(sorted1);
                for (int k = 0; k < result.count; k++) {
                    free(result.items[k].elements);
                }
                free(result.items);
                result.items = NULL;
                result.count = 0;
                result.capacity = 0;
                return result;
            }
            memcpy(sorted2, t2.elements, t2.count * sizeof(int));
            sort_int_array(sorted2, t2.count);

            Tuple st1;
            st1.elements = sorted1;
            st1.count = t1.count;

            Tuple st2;
            st2.elements = sorted2;
            st2.count = t2.count;

            if (tuple_equal(st1, st2)) {
                int found = 0;
                for (int k = 0; k < result.count; k++) {
                    Tuple r = result.items[k];
                    int *sorted_r = (int *)malloc(r.count * sizeof(int));
                    if (sorted_r == NULL) {
                        free(sorted1);
                        free(sorted2);
                        for (int m = 0; m < result.count; m++) {
                            free(result.items[m].elements);
                        }
                        free(result.items);
                        result.items = NULL;
                        result.count = 0;
                        result.capacity = 0;
                        return result;
                    }
                    memcpy(sorted_r, r.elements, r.count * sizeof(int));
                    sort_int_array(sorted_r, r.count);

                    Tuple sr;
                    sr.elements = sorted_r;
                    sr.count = r.count;

                    if (tuple_equal(st1, sr)) {
                        found = 1;
                        free(sorted_r);
                        break;
                    }
                    free(sorted_r);
                }

                if (!found) {
                    if (result.count >= result.capacity) {
                        int new_capacity = result.capacity * 2;
                        Tuple *new_items = (Tuple *)realloc(result.items, new_capacity * sizeof(Tuple));
                        if (new_items == NULL) {
                            free(sorted1);
                            free(sorted2);
                            for (int m = 0; m < result.count; m++) {
                                free(result.items[m].elements);
                            }
                            free(result.items);
                            result.items = NULL;
                            result.count = 0;
                            result.capacity = 0;
                            return result;
                        }
                        result.items = new_items;
                        result.capacity = new_capacity;
                    }
                    Tuple new_tuple;
                    new_tuple.count = t1.count;
                    new_tuple.elements = (int *)malloc(new_tuple.count * sizeof(int));
                    if (new_tuple.elements == NULL) {
                        free(sorted1);
                        free(sorted2);
                        for (int m = 0; m < result.count; m++) {
                            free(result.items[m].elements);
                        }
                        free(result.items);
                        result.items = NULL;
                        result.count = 0;
                        result.capacity = 0;
                        return result;
                    }
                    memcpy(new_tuple.elements, t1.elements, t1.count * sizeof(int));
                    result.items[result.count++] = new_tuple;
                }
            }
            free(sorted2);
        }
        free(sorted1);
    }
    return result;
}

int main() {
    Tuple t1 = { .count = 3 };
    t1.elements = (int *)malloc(3 * sizeof(int));
    t1.elements[0] = 1;
    t1.elements[1] = 2;
    t1.elements[2] = 3;

    Tuple t2 = { .count = 3 };
    t2.elements = (int *)malloc(3 * sizeof(int));
    t2.elements[0] = 3;
    t2.elements[1] = 2;
    t2.elements[2] = 1;

    Tuple t3 = { .count = 2 };
    t3.elements = (int *)malloc(2 * sizeof(int));
    t3.elements[0] = 4;
    t3.elements[1] = 5;

    Tuple t4 = { .count = 3 };
    t4.elements = (int *)malloc(3 * sizeof(int));
    t4.elements[0] = 1;
    t4.elements[1] = 2;
    t4.elements[2] = 3;

    TupleList list1 = { .count = 2, .capacity = 2 };
    list1.items = (Tuple *)malloc(2 * sizeof(Tuple));
    list1.items[0] = t1;
    list1.items[1] = t3;

    TupleList list2 = { .count = 2, .capacity = 2 };
    list2.items = (Tuple *)malloc(2 * sizeof(Tuple));
    list2.items[0] = t2;
    list2.items[1] = t4;

    TupleList intersection = find_tuple_intersection(list1, list2);

    for (int i = 0; i < intersection.count; i++) {
        for (int j = 0; j < intersection.items[i].count; j++) {
            printf("%d ", intersection.items[i].elements[j]);
        }
        printf("\n");
    }

    for (int i = 0; i < intersection.count; i++) {
        free(intersection.items[i].elements);
    }
    free(intersection.items);

    free(t1.elements);
    free(t2.elements);
    free(t3.elements);
    free(t4.elements);
    free(list1.items);
    free(list2.items);

    return 0;
}