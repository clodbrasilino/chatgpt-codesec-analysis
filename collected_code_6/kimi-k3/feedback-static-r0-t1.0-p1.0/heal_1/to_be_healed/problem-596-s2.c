#include <stdio.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'Tuple::x' is never used. [unusedStructMember]
     */
    int x;
    /* Possible weaknesses found:
     *  struct member 'Tuple::y' is never used. [unusedStructMember]
     */
    double y;
    /* Possible weaknesses found:
     *  struct member 'Tuple::z' is never used. [unusedStructMember]
     */
    char z;
} Tuple;

size_t get_tuple_size(const Tuple *tuple) {
    if (tuple == NULL) {
        return 0;
    }
    return sizeof(*tuple);
}

int main(void) {
    Tuple t = {1, 2.5, 'a'};
    size_t size = get_tuple_size(&t);
    
    if (size > 0) {
        printf("Size of tuple: %zu bytes\n", size);
    } else {
        fprintf(stderr, "Error: Invalid tuple\n");
        return 1;
    }
    
    return 0;
}