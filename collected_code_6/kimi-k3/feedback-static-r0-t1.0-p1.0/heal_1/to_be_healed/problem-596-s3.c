#include <stdio.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'Tuple::id' is never used. [unusedStructMember]
     */
    int id;
    /* Possible weaknesses found:
     *  struct member 'Tuple::value' is never used. [unusedStructMember]
     */
    double value;
    /* Possible weaknesses found:
     *  struct member 'Tuple::label' is never used. [unusedStructMember]
     */
    char label[32];
} Tuple;

size_t tuple_size(const Tuple *t) {
    if (t == NULL) {
        return 0;
    }
    return sizeof(*t);
}

int main(void) {
    Tuple t = {1, 3.14, "example"};
    size_t size = tuple_size(&t);
    if (size > 0) {
        printf("%zu\n", size);
    }
    return 0;
}