#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

void freeTuple(Tuple *t) {
    free(t->data);
    t->data = NULL;
    t->length = 0;
}

Tuple createTuple(int arr[], size_t len) {
    Tuple t;
    t.data = (int *)malloc(len * sizeof(int));
    for (size_t i = 0; i < len; ++i) {
        t.data[i] = arr[i];
    }
    t.length = len;
    return t;
}

Tuple removeMatchingTuples(const Tuple *a, const Tuple *b) {
    if (a->length == 0 || b->length == 0) {
        return createTuple(NULL, 0);
    }

    int *resultData = (int *)malloc(a->length * sizeof(int));
    size_t resultLength = 0;

    for (size_t i = 0; i < a->length; ++i) {
        int found = 0;
        for (size_t j = 0; j < b->length; ++j) {
            if (a->data[i] == b->data[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            resultData[resultLength++] = a->data[i];
        }
    }

    Tuple result = {resultData, resultLength};
    return result;
}

int main() {
    int arrA[] = {1, 2, 3, 4, 5};
    int arrB[] = {2, 4};

    Tuple tupleA = createTuple(arrA, sizeof(arrA) / sizeof(arrA[0]));
    Tuple tupleB = createTuple(arrB, sizeof(arrB) / sizeof(arrB[0]));

    Tuple result = removeMatchingTuples(&tupleA, &tupleB);

    for (size_t i = 0; i < result.length; ++i) {
        printf("%d ", result.data[i]);
    }

    freeTuple(&tupleA);
    freeTuple(&tupleB);
    freeTuple(&result);

    return 0;
}