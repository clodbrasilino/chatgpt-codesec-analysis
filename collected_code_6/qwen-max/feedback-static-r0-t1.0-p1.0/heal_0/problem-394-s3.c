#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

int is_distinct(Tuple t) {
    for (size_t i = 0; i < t.length; ++i) {
        for (size_t j = i + 1; j < t.length; ++j) {
            if (t.elements[i] == t.elements[j]) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    int data1[] = {1, 2, 3, 4};
    int data2[] = {1, 2, 2, 4};

    Tuple t1 = {data1, sizeof(data1) / sizeof(data1[0])};
    Tuple t2 = {data2, sizeof(data2) / sizeof(data2[0])};

    if (is_distinct(t1)) {
        printf("The first tuple is distinct.\n");
    } else {
        printf("The first tuple is not distinct.\n");
    }

    if (is_distinct(t2)) {
        printf("The second tuple is distinct.\n");
    } else {
        printf("The second tuple is not distinct.\n");
    }

    return 0;
}