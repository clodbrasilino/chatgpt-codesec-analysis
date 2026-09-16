#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int first;
    int second;
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

bool are_lists_identical(TupleList list1, TupleList list2) {
    if (list1.len != list2.len) {
        return false;
    }
    for (size_t i = 0; i < list1.len; i++) {
        if (list1.data[i].first != list2.data[i].first || list1.data[i].second != list2.data[i].second) {
            return false;
        }
    }
    return true;
}

int main(void) {
    TupleList list1 = create_tuple_list(3);
    list1.data[0].first = 1; list1.data[0].second = 2;
    list1.data[1].first = 3; list1.data[1].second = 4;
    list1.data[2].first = 5; list1.data[2].second = 6;

    TupleList list2 = create_tuple_list(3);
    list2.data[0].first = 1; list2.data[0].second = 2;
    list2.data[1].first = 3; list2.data[1].second = 4;
    list2.data[2].first = 5; list2.data[2].second = 6;

    TupleList list3 = create_tuple_list(2);
    list3.data[0].first = 1; list3.data[0].second = 2;
    list3.data[1].first = 3; list3.data[1].second = 4;

    bool res1 = are_lists_identical(list1, list2);
    bool res2 = are_lists_identical(list1, list3);

    printf("%d\n", res1);
    printf("%d\n", res2);

    free_tuple_list(list1);
    free_tuple_list(list2);
    free_tuple_list(list3);

    return 0;
}