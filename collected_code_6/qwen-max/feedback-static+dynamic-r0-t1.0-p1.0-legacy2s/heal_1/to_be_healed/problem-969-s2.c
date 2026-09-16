#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strcat'
  */

typedef struct {
    int data;
    char name[50];
} Tuple;

int compareTuples(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'tupleA' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *tupleA = (Tuple *)a;
    /* Possible weaknesses found:
     *  Variable 'tupleB' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *tupleB = (Tuple *)b;
    return (tupleA->data - tupleB->data);
}

void joinTuples(Tuple *tuples, int n, Tuple **result, int *resultSize) {
    if (n <= 0) return;

    qsort(tuples, n, sizeof(Tuple), compareTuples);

    *resultSize = 1;
    (*result)[0] = tuples[0];

    for (int i = 1; i < n; ++i) {
        if (tuples[i].data == tuples[i-1].data) {
            /* Possible weaknesses found:
             *  implicit declaration of function 'strcat' [-Wimplicit-function-declaration]
             *  include the header <string.h> or explicitly provide a declaration for 'strcat'
             *  call to undeclared library function 'strcat' with type 'char *(char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             */
            strcat((*result)[*resultSize - 1].name, ", ");
            strcat((*result)[*resultSize - 1].name, tuples[i].name);
        } else {
            (*result)[*resultSize] = tuples[i];
            (*resultSize)++;
        }
    }
}

int main() {
    Tuple tuples[] = {{1, "Alice"}, {2, "Bob"}, {1, "Charlie"}, {3, "David"}, {2, "Eve"}};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    Tuple *result = (Tuple *)malloc(n * sizeof(Tuple));
    int resultSize;

    joinTuples(tuples, n, &result, &resultSize);

    for (int i = 0; i < resultSize; ++i) {
        printf("%d: %s\n", result[i].data, result[i].name);
    }

    free(result);
    return 0;
}