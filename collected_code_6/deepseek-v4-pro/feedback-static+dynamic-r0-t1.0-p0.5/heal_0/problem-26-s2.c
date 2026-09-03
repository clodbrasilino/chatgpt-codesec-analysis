#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

bool has_all_k_elements(TupleList *list, int k) {
    if (list == NULL || k <= 0) {
        return false;
    }

    bool *seen = (bool *)calloc(k, sizeof(bool));
    if (seen == NULL) {
        return false;
    }

    for (int i = 0; i < list->count; i++) {
        for (int j = 0; j < list->tuples[i].size; j++) {
            int elem = list->tuples[i].elements[j];
            if (elem >= 0 && elem < k) {
                seen[elem] = true;
            }
        }
    }

    for (int i = 0; i < k; i++) {
        if (!seen[i]) {
            free(seen);
            return false;
        }
    }

    free(seen);
    return true;
}

int main(void) {
    int elements1[] = {0, 1, 2};
    int elements2[] = {3, 4};
    int elements3[] = {5};

    Tuple tuples[3] = {
        {elements1, 3},
        {elements2, 2},
        {elements3, 1}
    };

    TupleList list = {tuples, 3};

    if (has_all_k_elements(&list, 6)) {
        printf("All elements present\n");
    } else {
        printf("Not all elements present\n");
    }

    return 0;
}