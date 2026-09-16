#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple *data;
    size_t len;
} TupleList;

TupleList create_tuple_list(size_t len) {
    TupleList list;
    list.len = len;
    if (len > 0) {
        list.data = (Tuple *)malloc(len * sizeof(Tuple));
        if (list.data == NULL) {
            exit(EXIT_FAILURE);
        }
    } else {
        list.data = NULL;
    }
    return list;
}

void free_tuple_list(TupleList list) {
    free(list.data);
}

bool are_tuple_lists_identical(TupleList list1, TupleList list2) {
    if (list1.len != list2.len) {
        return false;
    }
    for (size_t i = 0; i < list1.len; i++) {
        if (list1.data[i].a != list2.data[i].a || list1.data[i].b != list2.data[i].b) {
            return false;
        }
    }
    return true;
}

int main(void) {
    TupleList list1 = create_tuple_list(3);
    list1.data[0].a = 1; list1.data[0].b = 2;
    list1.data[1].a = 3; list1.data[1].b = 4;
    list1.data[2].a = 5; list1.data[2].b = 6;

    TupleList list2 = create_tuple_list(3);
    list2.data[0].a = 1; list2.data[0].b = 2;
    list2.data[1].a = 3; list2.data[1].b = 4;
    list2.data[2].a = 5; list2.data[2].b = 6;

    TupleList list3 = create_tuple_list(2);
    list3.data[0].a = 1; list3.data[0].b = 2;
    list3.data[1].a = 3; list3.data[1].b = 4;

    TupleList list4 = create_tuple_list(3);
    list4.data[0].a = 1; list4.data[0].b = 2;
    list4.data[1].a = 3; list4.data[1].b = 4;
    list4.data[2].a = 7; list4.data[2].b = 6;

    if (are_tuple_lists_identical(list1, list2)) {
        printf("list1 and list2 are identical\n");
    } else {
        printf("list1 and list2 are not identical\n");
    }

    if (are_tuple_lists_identical(list1, list3)) {
        printf("list1 and list3 are identical\n");
    } else {
        printf("list1 and list3 are not identical\n");
    }

    if (are_tuple_lists_identical(list1, list4)) {
        printf("list1 and list4 are identical\n");
    } else {
        printf("list1 and list4 are not identical\n");
    }

    free_tuple_list(list1);
    free_tuple_list(list2);
    free_tuple_list(list3);
    free_tuple_list(list4);

    return 0;
}