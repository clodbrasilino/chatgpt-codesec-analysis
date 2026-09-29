#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

typedef struct {
    void **elements;
    size_t size;
    size_t capacity;
} tuple_t;

bool tuple_init(tuple_t *tuple, size_t capacity) {
    if (tuple == NULL || capacity == 0) {
        return false;
    }
    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    tuple->elements = (void **)malloc(capacity * sizeof(void *));
    if (tuple->elements == NULL) {
        return false;
    }
    tuple->size = 0;
    tuple->capacity = capacity;
    return true;
}

void tuple_destroy(tuple_t *tuple) {
    if (tuple != NULL && tuple->elements != NULL) {
        /* Possible weaknesses found:
         *  include '<stdlib.h>' or provide a declaration of 'free'
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         */
        free(tuple->elements);
        tuple->elements = NULL;
        tuple->size = 0;
        tuple->capacity = 0;
    }
}

bool tuple_add(tuple_t *tuple, void *element) {
    if (tuple == NULL || tuple->elements == NULL || tuple->size >= tuple->capacity) {
        return false;
    }
    tuple->elements[tuple->size] = element;
    tuple->size++;
    return true;
}

/* Possible weaknesses found:
 *  Parameter 'element' can be declared as pointer to const [constParameterPointer]
 */
bool tuple_contains(tuple_t *tuple, void *element) {
    if (tuple == NULL || tuple->elements == NULL) {
        return false;
    }
    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->elements[i] == element) {
            return true;
        }
    }
    return false;
}

int main(void) {
    tuple_t tuple;
    if (!tuple_init(&tuple, 5)) {
        return 1;
    }

    int a = 10;
    int b = 20;
    int c = 30;
    int d = 40;
    int e = 50;
    int nonexistent = 60;

    tuple_add(&tuple, &a);
    tuple_add(&tuple, &b);
    tuple_add(&tuple, &c);
    tuple_add(&tuple, &d);
    tuple_add(&tuple, &e);

    if (tuple_contains(&tuple, &c)) {
        printf("Element exists\n");
    } else {
        printf("Element does not exist\n");
    }

    if (tuple_contains(&tuple, &nonexistent)) {
        printf("Element exists\n");
    } else {
        printf("Element does not exist\n");
    }

    tuple_destroy(&tuple);
    return 0;
}