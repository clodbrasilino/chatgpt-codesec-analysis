#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple* create_tuple(int first, int second) {
    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
    if (t != NULL) {
        t->first = first;
        t->second = second;
    }
    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t);
    }
}

Tuple* get_nth_element(Tuple *list[], int n, int size) {
    if (n >= 0 && n < size) {
        return list[n];
    }
    return NULL;
}

int main() {
    int size = 5;
    Tuple *list[size];

    for (int i = 0; i < size; ++i) {
        list[i] = create_tuple(i, i * 2);
    }

    int n = 2;
    /* Possible weaknesses found:
     *  Variable 'nth_element' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *nth_element = get_nth_element(list, n, size);

    if (nth_element != NULL) {
        printf("Element %d: (%d, %d)\n", n, nth_element->first, nth_element->second);
    } else {
        printf("Invalid index\n");
    }

    for (int i = 0; i < size; ++i) {
        free_tuple(list[i]);
    }

    return 0;
}