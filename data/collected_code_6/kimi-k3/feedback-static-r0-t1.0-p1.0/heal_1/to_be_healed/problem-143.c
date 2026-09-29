#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'free'
  */

typedef enum {
    TYPE_INT,
    TYPE_LIST
} ElementType;

typedef struct {
    ElementType type;
    union {
        int value;
        struct {
            int *items;
            size_t count;
        } list;
    } data;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t count;
} Tuple;

size_t count_lists_in_tuple(const Tuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL) {
        return 0;
    }
    
    size_t list_count = 0;
    for (size_t i = 0; i < tuple->count; i++) {
        if (tuple->elements[i].type == TYPE_LIST) {
            list_count++;
        }
    }
    return list_count;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    
    if (tuple->elements != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            if (tuple->elements[i].type == TYPE_LIST && 
                tuple->elements[i].data.list.items != NULL) {
                /* Possible weaknesses found:
                 *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
                 *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
                 *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
                 */
                free(tuple->elements[i].data.list.items);
                tuple->elements[i].data.list.items = NULL;
            }
        }
        free(tuple->elements);
        tuple->elements = NULL;
    }
    tuple->count = 0;
}

int main(void) {
    Tuple tuple = {0};
    size_t num_elements = 5;
    
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'calloc'
     *  call to undeclared library function 'calloc' with type 'void *(unsigned long, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'calloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'calloc'
     */
    tuple.elements = calloc(num_elements, sizeof(TupleElement));
    if (tuple.elements == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    tuple.count = num_elements;
    
    tuple.elements[0].type = TYPE_INT;
    tuple.elements[0].data.value = 42;
    
    tuple.elements[1].type = TYPE_LIST;
    tuple.elements[1].data.list.count = 3;
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     */
    tuple.elements[1].data.list.items = malloc(3 * sizeof(int));
    if (tuple.elements[1].data.list.items == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_tuple(&tuple);
        return 1;
    }
    tuple.elements[1].data.list.items[0] = 1;
    tuple.elements[1].data.list.items[1] = 2;
    tuple.elements[1].data.list.items[2] = 3;
    
    tuple.elements[2].type = TYPE_INT;
    tuple.elements[2].data.value = 100;
    
    tuple.elements[3].type = TYPE_LIST;
    tuple.elements[3].data.list.count = 2;
    tuple.elements[3].data.list.items = malloc(2 * sizeof(int));
    if (tuple.elements[3].data.list.items == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_tuple(&tuple);
        return 1;
    }
    tuple.elements[3].data.list.items[0] = 10;
    tuple.elements[3].data.list.items[1] = 20;
    
    tuple.elements[4].type = TYPE_INT;
    tuple.elements[4].data.value = 7;
    
    size_t result = count_lists_in_tuple(&tuple);
    printf("Number of lists in tuple: %zu\n", result);
    
    free_tuple(&tuple);
    return 0;
}