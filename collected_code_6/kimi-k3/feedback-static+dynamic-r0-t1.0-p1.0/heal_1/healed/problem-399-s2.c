#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

int tuple_xor(const Tuple *t1, const Tuple *t2, Tuple *result) {
    size_t min_size;
    
    if (t1 == NULL || t2 == NULL || result == NULL) {
        return -1;
    }
    
    if (t1->data == NULL || t2->data == NULL) {
        return -1;
    }
    
    min_size = (t1->size < t2->size) ? t1->size : t2->size;
    
    result->data = (int *)malloc(min_size * sizeof(int));
    if (result->data == NULL) {
        return -1;
    }
    
    result->size = min_size;
    
    for (size_t i = 0; i < min_size; i++) {
        result->data[i] = t1->data[i] ^ t2->data[i];
    }
    
    return 0;
}

void tuple_free(Tuple *t) {
    if (t != NULL && t->data != NULL) {
        free(t->data);
        t->data = NULL;
        t->size = 0;
    }
}

int main(void) {
    Tuple t1;
    Tuple t2;
    Tuple result;
    int data1[] = {5, 3, 8, 12};
    int data2[] = {2, 6, 8, 10};
    int status;
    
    t1.data = data1;
    t1.size = sizeof(data1) / sizeof(data1[0]);
    
    t2.data = data2;
    t2.size = sizeof(data2) / sizeof(data2[0]);
    
    result.data = NULL;
    result.size = 0;
    
    status = tuple_xor(&t1, &t2, &result);
    
    if (status == 0) {
        printf("Result: ");
        for (size_t i = 0; i < result.size; i++) {
            printf("%d ", result.data[i]);
        }
        printf("\n");
        tuple_free(&result);
    } else {
        fprintf(stderr, "Error performing XOR operation\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}