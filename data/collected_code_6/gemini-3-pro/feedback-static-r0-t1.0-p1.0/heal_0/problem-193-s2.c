#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int *elements;
    size_t size;
};

struct Tuple* removeDuplicates(const struct Tuple* inputTuple) {
    if (inputTuple == NULL || inputTuple->elements == NULL) {
        return NULL;
    }

    struct Tuple* resultTuple = (struct Tuple*)malloc(sizeof(struct Tuple));
    if (resultTuple == NULL) {
        return NULL;
    }

    if (inputTuple->size == 0) {
        resultTuple->size = 0;
        resultTuple->elements = NULL;
        return resultTuple;
    }

    resultTuple->elements = (int*)malloc(inputTuple->size * sizeof(int));
    if (resultTuple->elements == NULL) {
        free(resultTuple);
        return NULL;
    }

    size_t uniqueCount = 0;
    for (size_t i = 0; i < inputTuple->size; ++i) {
        int isDuplicate = 0;
        for (size_t j = 0; j < uniqueCount; ++j) {
            if (inputTuple->elements[i] == resultTuple->elements[j]) {
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate) {
            resultTuple->elements[uniqueCount++] = inputTuple->elements[i];
        }
    }

    if (uniqueCount < inputTuple->size) {
        int* temp = (int*)realloc(resultTuple->elements, uniqueCount * sizeof(int));
        if (temp != NULL || uniqueCount == 0) {
            resultTuple->elements = temp;
        }
    }

    resultTuple->size = uniqueCount;
    return resultTuple;
}

void printTuple(const struct Tuple* t) {
    if (t == NULL) {
        printf("NULL\n");
        return;
    }
    printf("(");
    for (size_t i = 0; i < t->size; ++i) {
        printf("%d%s", t->elements[i], (i < t->size - 1) ? ", " : "");
    }
    printf(")\n");
}

int main(void) {
    int data[] = {1, 2, 2, 3, 4, 4, 4, 5, 1};
    struct Tuple inputTuple = { data, sizeof(data) / sizeof(data[0]) };

    struct Tuple* uniqueTuple = removeDuplicates(&inputTuple);

    if (uniqueTuple != NULL) {
        printTuple(uniqueTuple);
        free(uniqueTuple->elements);
        free(uniqueTuple);
    }

    return 0;
}