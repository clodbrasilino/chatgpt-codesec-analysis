#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* elements;
    size_t length;
} Tuple;

int findCommonFirstElement(Tuple** tuples, size_t count) {
    if (count == 0) return -1;
    
    int first = (*tuples[0]).elements[0];
    for (size_t i = 1; i < count; ++i) {
        if ((*tuples[i]).elements[0] != first) return -1;
    }
    return first;
}

int main() {
    int elements1[] = {1, 2, 3};
    int elements2[] = {1, 4, 5};
    int elements3[] = {1, 6, 7};

    Tuple tuple1 = {elements1, 3};
    Tuple tuple2 = {elements2, 3};
    Tuple tuple3 = {elements3, 3};

    Tuple* tuples[] = {&tuple1, &tuple2, &tuple3};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    int common = findCommonFirstElement(tuples, count);
    if (common != -1) {
        printf("Common first element: %d\n", common);
    } else {
        printf("No common first element found.\n");
    }

    return 0;
}