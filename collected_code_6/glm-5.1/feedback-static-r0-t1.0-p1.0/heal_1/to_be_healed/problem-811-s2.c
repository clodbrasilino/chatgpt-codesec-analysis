#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple *data;
    size_t len;
} TupleList;

int are_tuple_lists_identical(const TupleList *list1, const TupleList *list2) {
    if (list1 == NULL || list2 == NULL) {
        return 0;
    }

    if (list1->len != list2->len) {
        return 0;
    }

    for (size_t i = 0; i < list1->len; i++) {
        if (list1->data[i].a != list2->data[i].a || list1->data[i].b != list2->data[i].b) {
            return 0;
        }
    }

    return 1;
}

TupleList create_tuple_list(const Tuple *items, size_t count) {
    TupleList list;
    list.len = count;
    if (count == 0) {
        list.data = NULL;
        return list;
    }
    list.data = (Tuple *)malloc(count * sizeof(Tuple));
    if (list.data == NULL) {
        list.len = 0;
        return list;
    }
    for (size_t i = 0; i < count; i++) {
        list.data[i] = items[i];
    }
    return list;
}

void free_tuple_list(TupleList *list) {
    if (list != NULL) {
        free(list->data);
        list->data = NULL;
        list->len = 0;
    }
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'items1' can be declared as const array [constVariable]
     */
    Tuple items1[] = {{1, 2}, {3, 4}, {5, 6}};
    /* Possible weaknesses found:
     *  Variable 'items2' can be declared as const array [constVariable]
     */
    Tuple items2[] = {{1, 2}, {3, 4}, {5, 6}};
    /* Possible weaknesses found:
     *  Variable 'items3' can be declared as const array [constVariable]
     */
    Tuple items3[] = {{1, 2}, {3, 4}, {7, 8}};
    /* Possible weaknesses found:
     *  Variable 'items4' can be declared as const array [constVariable]
     */
    Tuple items4[] = {{1, 2}};

    TupleList list1 = create_tuple_list(items1, 3);
    TupleList list2 = create_tuple_list(items2, 3);
    TupleList list3 = create_tuple_list(items3, 3);
    TupleList list4 = create_tuple_list(items4, 1);
    TupleList list5 = {NULL, 0};

    printf("%d\n", are_tuple_lists_identical(&list1, &list2));
    printf("%d\n", are_tuple_lists_identical(&list1, &list3));
    printf("%d\n", are_tuple_lists_identical(&list1, &list4));
    printf("%d\n", are_tuple_lists_identical(&list1, NULL));
    printf("%d\n", are_tuple_lists_identical(&list5, &list5));

    free_tuple_list(&list1);
    free_tuple_list(&list2);
    free_tuple_list(&list3);
    free_tuple_list(&list4);

    return 0;
}