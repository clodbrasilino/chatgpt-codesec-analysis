#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    float second;
} Tuple;

Tuple* create_tuple_list(int n) {
    Tuple *list = (Tuple *)malloc(n * sizeof(Tuple));
    for (int i = 0; i < n; ++i) {
        list[i].first = i * 2;
        list[i].second = (float)i / 2.0;
    }
    return list;
}

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
Tuple get_nth_element(Tuple *list, int n) {
    return list[n];
}

int main() {
    int n = 5;
    Tuple *tuple_list = create_tuple_list(n);
    if (tuple_list == NULL) {
        return 1;
    }

    int index = 2;
    Tuple nth_element = get_nth_element(tuple_list, index);
    printf("Tuple at index %d: (%d, %f)\n", index, nth_element.first, nth_element.second);

    free(tuple_list);
    return 0;
}