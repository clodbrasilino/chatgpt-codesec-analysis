#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple* create_tuple(int first, int second) {
    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    t->first = first;
    t->second = second;
    return t;
}

void free_tuples(Tuple *tuples, int size) {
    for (int i = 0; i < size; ++i) {
        /* Possible weaknesses found:
         *  passing 'Tuple' to parameter of incompatible type 'void *'
         *  incompatible type for argument 1 of 'free'
         */
        free(tuples[i]);
    }
    free(tuples);
}

/* Possible weaknesses found:
 *  Parameter 'tuples' can be declared as pointer to const [constParameterPointer]
 */
Tuple* get_nth_element(Tuple *tuples, int n, int size) {
    if (n < 0 || n >= size) {
        return NULL;
    }
    /* Possible weaknesses found:
     *  incompatible types when returning type 'Tuple' but 'Tuple *' was expected
     *  returning 'Tuple' from a function with incompatible result type 'Tuple *'; take the address with &
     */
    return tuples[n];
}

int main() {
    int size = 5;
    /* Possible weaknesses found:
     *  Size of pointer 'tuples' used instead of size of its data. [pointerSize]
     */
    Tuple *tuples = (Tuple *)malloc(size * sizeof(Tuple *));
    if (tuples == NULL) {
        return 1;
    }

    for (int i = 0; i < size; ++i) {
        /* Possible weaknesses found:
         *  assigning to 'Tuple' from incompatible type 'Tuple *'; dereference with *
         *  incompatible types when assigning to type 'Tuple' from type 'Tuple *'
         */
        tuples[i] = create_tuple(i, i * 2);
        /* Possible weaknesses found:
         *  invalid operands to binary == (have 'Tuple' and 'void *')
         *  invalid operands to binary expression ('Tuple' and 'void *')
         */
        if (tuples[i] == NULL) {
            free_tuples(tuples, i);
            return 1;
        }
    }

    int n = 3;
    /* Possible weaknesses found:
     *  Variable 'nth_element' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *nth_element = get_nth_element(tuples, n, size);
    if (nth_element != NULL) {
        printf("The %dth element: (%d, %d)\n", n, nth_element->first, nth_element->second);
    } else {
        printf("Invalid index\n");
    }

    /* Possible weaknesses found:
     *  expected 'void *' but argument is of type 'Tuple'
     *  passing argument to parameter here
     */
    free_tuples(tuples, size);
    return 0;
}