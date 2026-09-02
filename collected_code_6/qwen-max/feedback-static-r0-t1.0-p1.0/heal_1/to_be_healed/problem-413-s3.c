#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple* create_tuple(int first, int second) {
    Tuple* t = (Tuple*)malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    t->first = first;
    t->second = second;
    return t;
}

/* Possible weaknesses found:
 *  expected 'Tuple *' but argument is of type 'Tuple **'
 */
void free_tuples(Tuple* tuples, int length) {
    for (int i = 0; i < length; i++) {
        /* Possible weaknesses found:
         *  incompatible type for argument 1 of 'free'
         *  passing 'Tuple' to parameter of incompatible type 'void *'
         */
        free(tuples[i]);
    }
    free(tuples);
}

/* Possible weaknesses found:
 *  expected 'Tuple *' but argument is of type 'Tuple **'
 */
Tuple* nth_element(Tuple* tuples, int length, int n) {
    if (n >= 0 && n < length) {
        /* Possible weaknesses found:
         *  returning 'Tuple' from a function with incompatible result type 'Tuple *'; take the address with &
         *  incompatible types when returning type 'Tuple' but 'Tuple *' was expected
         */
        return tuples[n];
    } else {
        return NULL;
    }
}

int main() {
    int num_tuples = 5;
    Tuple* list_of_tuples[num_tuples];
    
    for (int i = 0; i < num_tuples; i++) {
        list_of_tuples[i] = create_tuple(i, i * 2);
    }

    int n = 3;
    /* Possible weaknesses found:
     *  passing argument 1 of 'nth_element' from incompatible pointer type [-Wincompatible-pointer-types]
     *  Variable 'nth' can be declared as pointer to const [constVariablePointer]
     */
    Tuple* nth = nth_element(list_of_tuples, num_tuples, n);

    if (nth != NULL) {
        printf("The %dth element: (%d, %d)\n", n, nth->first, nth->second);
    } else {
        printf("Index out of bounds\n");
    }

    /* Possible weaknesses found:
     *  passing argument 1 of 'free_tuples' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    free_tuples(list_of_tuples, num_tuples);
    return 0;
}