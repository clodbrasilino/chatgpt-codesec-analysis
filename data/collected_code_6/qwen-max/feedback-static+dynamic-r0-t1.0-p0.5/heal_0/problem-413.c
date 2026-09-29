#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple* create_tuple_list(int n) {
    Tuple *list = (Tuple*)malloc(n * sizeof(Tuple));
    for (int i = 0; i < n; ++i) {
        list[i].first = i;
        list[i].second = i * 2;
    }
    return list;
}

void free_tuple_list(Tuple *list) {
    free(list);
}

Tuple get_nth_element(Tuple *list, int n, int size) {
    if (n >= 0 && n < size) {
        return list[n];
    } else {
        Tuple empty = {0, 0};
        return empty;
    }
}

int main() {
    int n = 5;
    Tuple *tuple_list = create_tuple_list(n);

    int index = 2;
    Tuple element = get_nth_element(tuple_list, index, n);
    printf("Element at index %d: (%d, %d)\n", index, element.first, element.second);

    free_tuple_list(tuple_list);
    return 0;
}