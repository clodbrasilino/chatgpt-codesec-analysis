#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

int element_exists(const Tuple *t, int value) {
    size_t i;
    if (t == NULL || t->elements == NULL) {
        return 0;
    }
    for (i = 0; i < t->size; i++) {
        if (t->elements[i] == value) {
            return 1;
        }
    }
    return 0;
}

Tuple tuple_union(const Tuple *t1, const Tuple *t2) {
    Tuple result;
    size_t i;
    size_t max_size;
    size_t count = 0;

    result.elements = NULL;
    result.size = 0;

    if (t1 == NULL || t2 == NULL) {
        return result;
    }

    if (t1->elements == NULL && t2->elements == NULL) {
        return result;
    }

    max_size = t1->size + t2->size;
    if (max_size == 0) {
        return result;
    }

    result.elements = (int *)malloc(max_size * sizeof(int));
    if (result.elements == NULL) {
        return result;
    }

    if (t1->elements != NULL) {
        for (i = 0; i < t1->size; i++) {
            if (!element_exists(&result, t1->elements[i])) {
                result.elements[count] = t1->elements[i];
                count++;
            }
        }
    }

    if (t2->elements != NULL) {
        for (i = 0; i < t2->size; i++) {
            if (!element_exists(&result, t2->elements[i])) {
                result.elements[count] = t2->elements[i];
                count++;
            }
        }
    }

    result.size = count;

    if (count == 0) {
        free(result.elements);
        result.elements = NULL;
    } else if (count < max_size) {
        int *temp = (int *)realloc(result.elements, count * sizeof(int));
        if (temp != NULL) {
            result.elements = temp;
        }
    }

    return result;
}

void tuple_free(Tuple *t) {
    if (t != NULL) {
        free(t->elements);
        t->elements = NULL;
        t->size = 0;
    }
}

void print_tuple(const Tuple *t) {
    size_t i;
    if (t == NULL || t->elements == NULL) {
        printf("()\n");
        return;
    }
    printf("(");
    for (i = 0; i < t->size; i++) {
        printf("%d", t->elements[i]);
        if (i < t->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {4, 5, 6, 7, 8};

    Tuple t1 = {arr1, 5};
    Tuple t2 = {arr2, 5};

    Tuple result = tuple_union(&t1, &t2);

    printf("Tuple 1: ");
    print_tuple(&t1);

    printf("Tuple 2: ");
    print_tuple(&t2);

    printf("Union: ");
    print_tuple(&result);

    tuple_free(&result);

    return 0;
}